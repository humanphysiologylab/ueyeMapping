/*!
 * \file    eventthread.h
 * \date    10.07.2009
 * \author  IDS Imaging Development Systems GmbH
 *
 * \brief   eventthread class (inherits QThread) declaration
 *          to wait on a uEye event and signal a connected slot
 *
 * \par Last modified
 *      on $Date:$ by $Author:$
 *
 * \li  05.02.2014 - Added define EVENTTHREAD_WAIT_TIMEOUT
 */

#ifndef EVENTTHREAD_H_
#define EVENTTHREAD_H_

#include <QObject>
#include <QThread>
#include <ueye.h>

/*!
 * \defgroup EVENTTHREAD uEye events implementation
 * \{
 */

/*!
 * \brief Event thread implementation for camera list change handling
 *
 * eventthread class inherits QThread to use signal/slot mechanism to signal an
 * initialized uEye event to a connected slot. For each uEye event to wait for, should
 * be a seperate member of this eventthread class.
 * \note To use signal/slot mechanism no multiple inheritance from an Qt Object class
 * is allowed.
 */

#define EVENTTHREAD_WAIT_TIMEOUT    1000
class EventThread:public QThread
{
Q_OBJECT

public:
    /*!
     * \brief class standard constructor
     */
    EventThread ();
    /*!
     * \brief class standard destructor
     */
    virtual ~EventThread ();

    /*!
     * \brief starts waiting on a uEye event
     * \param hCam uEye camera handle
     * \param event waiting for
     */
    int start (HIDS hCam = 0,int event = 0);
    /*!
     * \brief stops waiting on a uEye event
     */
    void stop ();

signals:
    /*!
     * \brief Qt signal function to be emited, when the uEye event happens
     * \param event that happened
     */
    void eventhappen (int event);

protected:
    /*!
     * \brief EventThread run function. Waits for the uEye event.
     */
    void run ();

private:
    /* camera handle for waiting event */
    HIDS m_hCam;
    /* event waiting for */
    int m_event;
    /* event run switch */
    volatile bool m_bRunEventThread;
#ifndef __linux__
    /* on windows we need an Event handle member */
    HANDLE m_hEvent;
#endif

};

/*!
 * \}
 */ // end of doc group EVENTTHREAD

#endif /* EVENTTHREAD_H_ */
