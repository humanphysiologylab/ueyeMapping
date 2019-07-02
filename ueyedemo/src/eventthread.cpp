/*!
 * \file    eventthread.cpp
 * \date    10.07.2009
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   eventthread class (inherits QThread) implementation
 *          to wait on a uEye event and signal a connected slot
 *
 * \par Last modified
 *      on $Date:$ by $Author:$
 *
 * \li  05.02.2014 - Changed is_WaitEvent() timeout to prevent from losing events
 * \li  12.12.2014 - Add missing Windows events
 */

#include "eventthread.h"

EventThread::EventThread ()
{
    m_hCam = 0;
    m_event = 0;
    m_bRunEventThread = false;
#ifndef __linux__
    m_hEvent = 0;
#endif
}

EventThread::~EventThread ()
{

}

int EventThread::start (HIDS hCam,int event)
{
    int ret = 0;
    m_hCam = hCam;
    m_event = event;
#ifndef __linux__
    m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (m_hEvent == NULL)
    {
        return -1;
    }
    ret = is_InitEvent(m_hCam, m_hEvent, m_event);
#endif
    ret = is_EnableEvent (m_hCam, m_event);

    if (ret == 0)
    {
        //printf ("started event %d detection!\n", m_event);
        m_bRunEventThread = true;
        QThread::start (); // start the thread run function
    }

    return ret;
}

void EventThread::stop ()
{
    m_bRunEventThread = false;
}

void EventThread::run ()
{
    //printf ("start waiting on event %d\n", m_event);
    while (m_bRunEventThread)
    {
#ifdef __linux__
        if (is_WaitEvent (m_hCam, m_event, EVENTTHREAD_WAIT_TIMEOUT) == IS_SUCCESS)
#else
        if (WaitForSingleObject(m_hEvent, EVENTTHREAD_WAIT_TIMEOUT) == WAIT_OBJECT_0)
#endif
        {
            //printf ("event %d detected\n", m_event);
            emit eventhappen (m_event);
        }
    }
    m_bRunEventThread = FALSE;
    is_DisableEvent (m_hCam, m_event);
#ifndef __linux__
    is_ExitEvent(m_hCam, m_event);
    CloseHandle(m_hEvent);
#endif
    //printf ("stop waiting on event %d\n", m_event);
}

