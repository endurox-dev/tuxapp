#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <atmi.h>
#include <fml32.h>
#include <userlog.h>
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
 * Service entry
 * @return SUCCEED/FAIL
 */
void ENTRY (TPSVCINFO *p_svc)
{
    int ret = SUCCEED;
    UBFH *p_ub = (UBFH *)p_svc->data;

    userlog("Got call");

    /* allocate some stuff for more data to put in  */
    if (NULL==(p_ub = (UBFH *)tprealloc((char *)p_ub, 4096)))
    {
        ret=FAIL;
        goto out;
    }

/*
	if (FAIL==Badd(p_ub, T_STRING_2_FLD, "Hello World from XATMI server", 0L))
	{
		ret=FAIL;
		goto out;
	}
*/

    /* TODO: tpenqueue() to "ENTRYQ0" or "ENTRYQ1" 
     * these are auto-q, forwards to T 
     */

out:

    tpreturn(  ret==SUCCEED?TPSUCCESS:TPFAIL,
        0L,
        (char *)p_ub,
        0L,
        0L);

}

/**
 * Initialize the application
 * @param argc	argument count
 * @param argv	argument values
 * @return SUCCEED/FAIL
 */
int tpsvrinit(int argc, char** argv)
{
    int ret = SUCCEED;

    if(SUCCEED!=tpopen())
    {		
        userlog("tpopen() failed: %s",
            tpstrerror(tperrno));
        ret=FAIL;
        goto out;   
    }

    /* Advertise our service */
    if (SUCCEED!=tpadvertise("ENTRY", ENTRY))
    {
        userlog("Failed to advertise ENTRY: %s",
            tpstrerror(tperrno));
        ret=FAIL;
        goto out;
    }

out:
	return ret;
}

/**
 * Terminate the application
 */
void tpsvrdone(void)
{
    userlog("Uninitialising...");
    tpclose();
}

