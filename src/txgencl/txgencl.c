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

/** Number of messages to be submitted */
static int M_count=100;

/**
 * Initialise the application
 * @param argc	argument count
 * @param argv	argument values
 * @return SUCCEED/FAIL
 */
int init(int argc, char** argv)
{
    int ret = SUCCEED;

    if (argc>1)
    {
        M_count=atoi(argv[1]);
    }

    if (FAIL==tpinit(NULL))
    {
        userlog("Failed to Initialise: %s", tpstrerror(tperrno));
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
    tpterm();
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
    FLDLEN32 sz;
    int i;
    long id;
    short node;
    char msg[1024];
    
    /* Call sample server... */
    if (NULL==(p_ub = (FBFR32 *)tpalloc("FML32", NULL, 1024)))
    {
        userlog("Failed to tpalloc: %s",  tpstrerror(tperrno));
        ret=FAIL;
        goto out;
    }

    for (i=0; i<M_count; i++)
    {
        userlog("Processing... i=%d", i);
        
        node = i%2;
        
        if (FAIL==Fchg32(p_ub, T_NODE, 0, (char *)&node, 0L))
        {
            userlog("Failed to set T_NODE: %s",  
                Fstrerror32(Ferror32));
            ret=FAIL;
            goto out;
        }
        
        id = (long)time(NULL) + i;
        
        if (FAIL==Fchg32(p_ub, T_TX_ID, 0, (char *)&id, 0L))
        {
            userlog("Failed to set T_TX_ID: %s",  
                Fstrerror32(Ferror32));
            ret=FAIL;
            goto out;
        }
        
        snprintf(msg, sizeof(msg), "node: %hd, id=%ld", node, id);
        
        if (FAIL==Fchg32(p_ub, T_TX_DATA, 0, msg, 0L))
        {
            userlog("Failed to set T_TX_DATA: %s",  
                Fstrerror32(Ferror32));
            ret=FAIL;
            goto out;
        }
        
        if (FAIL==tpcall("ENTRY", (char *)p_ub, 0L, (char **)&p_ub, &rsplen, 0L))
        {
            userlog("Failed to call ENTRY: %s", tpstrerror(tperrno));
            ret=FAIL;
            goto out;
        }

        Fprint32(p_ub);

    }
	
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

    if (FAIL==init(argc, argv))
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

