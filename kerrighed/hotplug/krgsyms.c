/*
 *  Copyright (C) 2006-2007, Pascal Gallard, Kerlabs.
 */

#include <kerrighed/krgsyms.h>
#include <linux/krg_hashtable.h>

/*****************************************************************************/
/*                                                                           */
/*                          KERRIGHED KSYM MANAGEMENT                        */
/*                                                                           */
/*****************************************************************************/


#define KRGSYMS_HTABLE_SIZE 256

static hashtable_t *krgsyms_htable = NULL;
static void* krgsyms_table[KRGSYMS_TABLE_SIZE];

int krgsyms_register(enum krgsyms_val v, void* p)
{
	if( (v < 0) || (v >= KRGSYMS_TABLE_SIZE) ){
		printk("krgsyms_register: Incorrect krgsym value (%d)\n", v);
		BUG();
		return -1;
	};

	if(krgsyms_table[v])
		printk("krgsyms_register_symbol(%d, %p): value already set in table\n",
					 v, p);

	if(hashtable_find(krgsyms_htable, (unsigned long)p) != NULL)
	{
		printk("krgsyms_register_symbol(%d, %p): value already set in htable\n",
					 v, p);
		BUG();
	}

	hashtable_add(krgsyms_htable, (unsigned long)p, (void*)v);
	krgsyms_table[v] = p;

	return 0;
};

int krgsyms_unregister(enum krgsyms_val v)
{
	void *p;

	if( (v < 0) || (v >= KRGSYMS_TABLE_SIZE) ){
		printk("krgsyms_unregister: Incorrect krgsym value (%d)\n", v);
		BUG();
		return -1;
	};

	p = krgsyms_table[v];
	krgsyms_table[v] = NULL;
	hashtable_remove(krgsyms_htable, (unsigned long)p);

	return 0;
};

enum krgsyms_val krgsyms_export(void* p)
{
	enum krgsyms_val ret;

	ret = (enum krgsyms_val)hashtable_find(krgsyms_htable, (unsigned long)p);

	if ((p!=NULL) && (ret == KRGSYMS_UNDEF))
	  {
			printk ("undefined krgsymbol (0x%p)!", p);
			BUG();
		}

	return ret;
};

void* krgsyms_import(enum krgsyms_val v)
{
	if( (v < 0) || (v >= KRGSYMS_TABLE_SIZE) ){
		printk("krgsyms_import: Incorrect krgsym value (%d)\n", v);
		BUG();
		return NULL;
	};

	if ((v!=0) && (krgsyms_table[v] == NULL))
	{
		printk ("undefined krgsymbol (%d)\n", v);
		BUG();
	}

	return krgsyms_table[v];
};

int init_krgsyms(void)
{
	int i;

	krgsyms_htable = hashtable_new(KRGSYMS_HTABLE_SIZE);
	if(krgsyms_table == NULL) return -ENOMEM;

	for(i=0;i<KRGSYMS_TABLE_SIZE;i++){
		krgsyms_table[i] = NULL;
	};

	return 0;
};

void cleanup_krgsyms(void){
};
