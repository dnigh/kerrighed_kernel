/** Kerrighed MM Server.
 *  @file mm_server.h
 *
 *  @author Renaud Lottiaux
 */

#ifndef __MM_SERVER__
#define __MM_SERVER__



/*--------------------------------------------------------------------------*
 *                                                                          *
 *                                  TYPES                                   *
 *                                                                          *
 *--------------------------------------------------------------------------*/



typedef struct mm_munmap_msg {
	unique_id_t mm_id;
	unsigned long start;
	size_t len;
} mm_munmap_msg_t;



/*--------------------------------------------------------------------------*
 *                                                                          *
 *                              EXTERN FUNCTIONS                            *
 *                                                                          *
 *--------------------------------------------------------------------------*/



void mm_server_init (void);
void mm_server_finalize (void);


#endif // __MM_SERVER__
