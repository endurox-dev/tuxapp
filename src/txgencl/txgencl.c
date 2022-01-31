#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <atmi.h>
#include <userlog.h>
#include <fml32.h>
#include <test.fd.h>
#include <tuxapp.h>
/*---------------------------Externs------------------------------------*/
/*---------------------------Macros-------------------------------------*/
/*---------------------------Enums--------------------------------------*/
/*---------------------------Typedefs-----------------------------------*/
/*---------------------------Globals------------------------------------*/
/*---------------------------Statics------------------------------------*/
/*---------------------------Prototypes---------------------------------*/


/**
 * Initialise the application
 * @param argc	argument count
 * @param argv	argument values
 * @return SUCCEED/FAIL
 */
int init(int argc, char** argv)
{
	int ret = SUCCEED;

	userlog("Initializing...");

	if (SUCCEED!=tpinit(NULL))
	{
		userlog("Failed to Initialise: %s", 
			tpstrerror(tperrno));
		ret = FAIL;
		goto out;
	}

out:

	return ret;
}

/**
 * Terminate the application
 */
int uninit(int status)
{
	int ret = SUCCEED;
	
	userlog("Uninitialising...");
	
	ret = tpterm();
	
	return ret;
}

/**
 * Do processing (call some service)
 * @return SUCCEED/FAIL
 */
int process (void)
{
	int ret = SUCCEED;
	FBFR32 *p_ub = NULL;
	long rsplen;
	BFLDLEN sz;
	int i;
    long id;
    short node;
    char msg[1024];
    
	
    
    /* Call sample server... */
    if (NULL==(p_ub = (UBFH *)tpalloc("FML32", NULL, 1024)))
    {
        userlog("Failed to tpalloc: %s",  tpstrerror(tperrno));
        ret=FAIL;
        goto out;
    }

    for (i=0; i<10000; i++)
    {
        
        userlog("Processing... i=%d", i);
        
        node = i%2;
        
        if (SUCCEED!=Fchg32(p_ub, T_NODE, 0, (char *)&node, 0L))
        {
            userlog("Failed to set T_NODE: %s",  
                Bstrerror(Berror));
            ret=FAIL;
            goto out;
        }
        
        id = (long)time(NULL) + i;
        
        if (SUCCEED!=Fchg32(p_ub, T_TX_ID, 0, (char *)&id, 0L))
        {
            userlog("Failed to set T_TX_ID: %s",  
                Bstrerror(Berror));
            ret=FAIL;
            goto out;
        }
        
        snprintf(msg, sizeof(msg), "node: %hd, id=%ld", node, id);
        
        if (SUCCEED!=Fchg32(p_ub, T_TX_DATA, 0, msg, 0L))
        {
            userlog("Failed to set T_TX_DATA: %s",  
                Bstrerror(Berror));
            ret=FAIL;
            goto out;
        }
        
        if (FAIL==tpcall("ENTRY", (char *)p_ub, 0L, (char **)&p_ub, &rsplen, 0L))
        {
            userlog("Failed to call ENTRY: %s", tpstrerror(tperrno));
            ret=FAIL;
            goto out;
        }
    }
	
	Fprint32(p_ub);
	
out:


	/* free up config data... */
	if (NULL!=p_ub)
	{
		tpfree((char *)p_ub);
	}
	
	return ret;
}

/**
 * Main entry of th program
 * @param argc	argument count
 * @param argv	argument values
 * @return SUCCEED/FAIL
 */
int main(int argc, char** argv)
{
	int ret = SUCCEED;

	if (SUCCEED!=init(argc, argv))
	{
		userlog("Failed to Initialise!");
		ret=FAIL;
		goto out;
	}
	
	if (SUCCEED!=process())
	{
		userlog("Process failed!");
		ret=FAIL;
		goto out;
	}
    
out:
	uninit(ret);

	return ret;
}

