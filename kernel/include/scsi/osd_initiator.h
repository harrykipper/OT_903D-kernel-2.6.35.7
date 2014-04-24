
#ifndef __OSD_INITIATOR_H__
#define __OSD_INITIATOR_H__

#include "osd_protocol.h"
#include "osd_types.h"

#include <linux/blkdev.h>
#include <scsi/scsi_device.h>

/* Note: "NI" in comments below means "Not Implemented yet" */

#define OSD_VER1_SUPPORT y

enum osd_std_version {
	OSD_VER_NONE = 0,
	OSD_VER1 = 1,
	OSD_VER2 = 2,
};

struct osd_dev {
	struct scsi_device *scsi_device;
	unsigned def_timeout;

#ifdef OSD_VER1_SUPPORT
	enum osd_std_version version;
#endif
};

/* Unique Identification of an OSD device */
struct osd_dev_info {
	unsigned systemid_len;
	u8 systemid[OSD_SYSTEMID_LEN];
	unsigned osdname_len;
	u8 *osdname;
};

struct osd_dev *osduld_path_lookup(const char *dev_name);
struct osd_dev *osduld_info_lookup(const struct osd_dev_info *odi);
void osduld_put_device(struct osd_dev *od);

const struct osd_dev_info *osduld_device_info(struct osd_dev *od);
bool osduld_device_same(struct osd_dev *od, const struct osd_dev_info *odi);

/* Add/remove test ioctls from external modules */
typedef int (do_test_fn)(struct osd_dev *od, unsigned cmd, unsigned long arg);
int osduld_register_test(unsigned ioctl, do_test_fn *do_test);
void osduld_unregister_test(unsigned ioctl);

/* These are called by uld at probe time */
void osd_dev_init(struct osd_dev *od, struct scsi_device *scsi_device);
void osd_dev_fini(struct osd_dev *od);

int osd_auto_detect_ver(struct osd_dev *od,
	void *caps, struct osd_dev_info *odi);

static inline struct request_queue *osd_request_queue(struct osd_dev *od)
{
	return od->scsi_device->request_queue;
}

/* we might want to use function vector in the future */
static inline void osd_dev_set_ver(struct osd_dev *od, enum osd_std_version v)
{
#ifdef OSD_VER1_SUPPORT
	od->version = v;
#endif
}

static inline bool osd_dev_is_ver1(struct osd_dev *od)
{
#ifdef OSD_VER1_SUPPORT
	return od->version == OSD_VER1;
#else
	return false;
#endif
}

struct osd_request;
typedef void (osd_req_done_fn)(struct osd_request *or, void *private);

struct osd_request {
	struct osd_cdb cdb;
	struct osd_data_out_integrity_info out_data_integ;
	struct osd_data_in_integrity_info in_data_integ;

	struct osd_dev *osd_dev;
	struct request *request;

	struct _osd_req_data_segment {
		void *buff;
		unsigned alloc_size; /* 0 here means: don't call kfree */
		unsigned total_bytes;
	} set_attr, enc_get_attr, get_attr;

	struct _osd_io_info {
		struct bio *bio;
		u64 total_bytes;
		u64 residual;
		struct request *req;
		struct _osd_req_data_segment *last_seg;
		u8 *pad_buff;
	} out, in;

	gfp_t alloc_flags;
	unsigned timeout;
	unsigned retries;
	unsigned sense_len;
	u8 sense[OSD_MAX_SENSE_LEN];
	enum osd_attributes_mode attributes_mode;

	osd_req_done_fn *async_done;
	void *async_private;
	int async_error;
	int req_errors;
};

static inline bool osd_req_is_ver1(struct osd_request *or)
{
	return osd_dev_is_ver1(or->osd_dev);
}


struct osd_request *osd_start_request(struct osd_dev *od, gfp_t gfp);

enum osd_req_options {
	OSD_REQ_FUA = 0x08,	/* Force Unit Access */
	OSD_REQ_DPO = 0x10,	/* Disable Page Out */

	OSD_REQ_BYPASS_TIMESTAMPS = 0x80,
};

int osd_finalize_request(struct osd_request *or,
	u8 options, const void *cap, const u8 *cap_key);

int osd_execute_request(struct osd_request *or);

int osd_execute_request_async(struct osd_request *or,
	osd_req_done_fn *done, void *private);


enum osd_err_priority {
	OSD_ERR_PRI_NO_ERROR	= 0,
	/* Recoverable, caller should clear_highpage() all pages */
	OSD_ERR_PRI_CLEAR_PAGES = 1, /* -EFAULT */
	OSD_ERR_PRI_RESOURCE	= 2, /* -ENOMEM */
	OSD_ERR_PRI_BAD_CRED	= 3, /* -EINVAL */
	OSD_ERR_PRI_NO_ACCESS	= 4, /* -EACCES */
	OSD_ERR_PRI_UNREACHABLE	= 5, /* any other */
	OSD_ERR_PRI_NOT_FOUND	= 6, /* -ENOENT */
	OSD_ERR_PRI_NO_SPACE	= 7, /* -ENOSPC */
	OSD_ERR_PRI_EIO		= 8, /* -EIO    */
};

struct osd_sense_info {
	enum osd_err_priority osd_err_pri;

	int key;		/* one of enum scsi_sense_keys */
	int additional_code ;	/* enum osd_additional_sense_codes */
	union { /* Sense specific information */
		u16 sense_info;
		u16 cdb_field_offset; 	/* scsi_invalid_field_in_cdb */
	};
	union { /* Command specific information */
		u64 command_info;
	};

	u32 not_initiated_command_functions; /* osd_command_functions_bits */
	u32 completed_command_functions; /* osd_command_functions_bits */
	struct osd_obj_id obj;
	struct osd_attr attr;
};

int osd_req_decode_sense_full(struct osd_request *or,
	struct osd_sense_info *osi, bool silent,
	struct osd_obj_id *bad_obj_list, int max_obj,
	struct osd_attr *bad_attr_list, int max_attr);

static inline int osd_req_decode_sense(struct osd_request *or,
	struct osd_sense_info *osi)
{
	return osd_req_decode_sense_full(or, osi, false, NULL, 0, NULL, 0);
}

void osd_end_request(struct osd_request *or);


void osd_req_set_master_seed_xchg(struct osd_request *or, ...);/* NI */
void osd_req_set_master_key(struct osd_request *or, ...);/* NI */

void osd_req_format(struct osd_request *or, u64 tot_capacity);

int osd_req_list_dev_partitions(struct osd_request *or,
	osd_id initial_id, struct osd_obj_id_list *list, unsigned nelem);

void osd_req_flush_obsd(struct osd_request *or,
	enum osd_options_flush_scope_values);

void osd_req_perform_scsi_command(struct osd_request *or,
	const u8 *cdb, ...);/* NI */
void osd_req_task_management(struct osd_request *or, ...);/* NI */

void osd_req_create_partition(struct osd_request *or, osd_id partition);
void osd_req_remove_partition(struct osd_request *or, osd_id partition);

void osd_req_set_partition_key(struct osd_request *or,
	osd_id partition, u8 new_key_id[OSD_CRYPTO_KEYID_SIZE],
	u8 seed[OSD_CRYPTO_SEED_SIZE]);/* NI */

int osd_req_list_partition_collections(struct osd_request *or,
	osd_id partition, osd_id initial_id, struct osd_obj_id_list *list,
	unsigned nelem);

int osd_req_list_partition_objects(struct osd_request *or,
	osd_id partition, osd_id initial_id, struct osd_obj_id_list *list,
	unsigned nelem);

void osd_req_flush_partition(struct osd_request *or,
	osd_id partition, enum osd_options_flush_scope_values);

void osd_req_create_collection(struct osd_request *or,
	const struct osd_obj_id *);/* NI */
void osd_req_remove_collection(struct osd_request *or,
	const struct osd_obj_id *);/* NI */

/* list all objects in the collection */
int osd_req_list_collection_objects(struct osd_request *or,
	const struct osd_obj_id *, osd_id initial_id,
	struct osd_obj_id_list *list, unsigned nelem);

/* V2 only filtered list of objects in the collection */
void osd_req_query(struct osd_request *or, ...);/* NI */

void osd_req_flush_collection(struct osd_request *or,
	const struct osd_obj_id *, enum osd_options_flush_scope_values);

void osd_req_get_member_attrs(struct osd_request *or, ...);/* V2-only NI */
void osd_req_set_member_attrs(struct osd_request *or, ...);/* V2-only NI */

void osd_req_create_object(struct osd_request *or, struct osd_obj_id *);
void osd_req_remove_object(struct osd_request *or, struct osd_obj_id *);

void osd_req_write(struct osd_request *or,
	const struct osd_obj_id *obj, u64 offset, struct bio *bio, u64 len);
int osd_req_write_kern(struct osd_request *or,
	const struct osd_obj_id *obj, u64 offset, void *buff, u64 len);
void osd_req_append(struct osd_request *or,
	const struct osd_obj_id *, struct bio *data_out);/* NI */
void osd_req_create_write(struct osd_request *or,
	const struct osd_obj_id *, struct bio *data_out, u64 offset);/* NI */
void osd_req_clear(struct osd_request *or,
	const struct osd_obj_id *, u64 offset, u64 len);/* NI */
void osd_req_punch(struct osd_request *or,
	const struct osd_obj_id *, u64 offset, u64 len);/* V2-only NI */

void osd_req_flush_object(struct osd_request *or,
	const struct osd_obj_id *, enum osd_options_flush_scope_values,
	/*V2*/ u64 offset, /*V2*/ u64 len);

void osd_req_read(struct osd_request *or,
	const struct osd_obj_id *obj, u64 offset, struct bio *bio, u64 len);
int osd_req_read_kern(struct osd_request *or,
	const struct osd_obj_id *obj, u64 offset, void *buff, u64 len);


/* get before set */
void osd_req_get_attributes(struct osd_request *or, const struct osd_obj_id *);

/* set before get */
void osd_req_set_attributes(struct osd_request *or, const struct osd_obj_id *);


/* Attributes List mode (or V2 CDB) */
  /*
   * TODO: In ver2 if at finalize time only one attr was set and no gets,
   * then the Attributes CDB mode is used automatically to save IO.
   */

/* set a list of attributes. */
int osd_req_add_set_attr_list(struct osd_request *or,
	const struct osd_attr *, unsigned nelem);

/* get a list of attributes */
int osd_req_add_get_attr_list(struct osd_request *or,
	const struct osd_attr *, unsigned nelem);

int osd_req_decode_get_attr_list(struct osd_request *or,
	struct osd_attr *, int *nelem, void **iterator);

/* Attributes Page mode */

int osd_req_add_get_attr_page(struct osd_request *or,
	u32 page_id, void *attr_page_data, unsigned max_page_len,
	const struct osd_attr *set_one);

#endif /* __OSD_LIB_H__ */
