/** Global management of faf files interface.
 *  @file faf_file_mgr.h
 *
 *  @author Renaud Lottiaux
 */
#ifndef __FAF_FILE_MGR__
#define __FAF_FILE_MGR__

#include <kerrighed/action.h>
#include <kerrighed/ghost.h>

/*--------------------------------------------------------------------------*
 *                                                                          *
 *                            EXTERN VARIABLES                              *
 *                                                                          *
 *--------------------------------------------------------------------------*/

extern struct dvfs_mobility_operations dvfs_mobility_faf_ops;
extern struct kmem_cache *faf_client_data_cachep;

/*--------------------------------------------------------------------------*
 *                                                                          *
 *                              EXTERN FUNCTIONS                            *
 *                                                                          *
 *--------------------------------------------------------------------------*/

struct file *create_faf_file_from_krg_desc(struct task_struct *task,
					   void *_desc);

int get_faf_file_krg_desc(struct file *file, void **desc, int *desc_size);

int cr_link_to_faf_file(struct epm_action *action, ghost_t *ghost,
			struct task_struct *task, struct file **returned_file,
			long key);
#endif // __FAF_FILE_MGR__
