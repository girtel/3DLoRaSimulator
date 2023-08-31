//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef INET_COMMON_VENERIS_EXTERNALCLOCKSCHEDULER_H_
#define INET_COMMON_VENERIS_EXTERNALCLOCKSCHEDULER_H_
#include <omnetpp/cscheduler.h>
#include "inet/common/INETDefs.h"
namespace inet {


//This scheduler is used with the ExecutionServer to advance the simulation time to the latest allowed time which is received in a message. That is, to keep the simulation
//synchronized with an external entity, for instance, a Unity program.
class ExternalClockScheduler : public omnetpp::cScheduler {
protected:
    simtime_t t_external;
public:
    ExternalClockScheduler();
    virtual ~ExternalClockScheduler();

    void setExternalTime(simtime_t _t_external);


    /**
     * Called at the beginning of a simulation run.
     */
    virtual void startRun();

    virtual std::string str() const override;
    /**
     * Return the likely next event in the simulation. This method is for UI
     * purposes, it does not play any role in the simulation. A basic
     * implementation would just return a pointer to the first event in the FES,
     * which is accurate for sequential simulation; with parallel, distributed or
     * real-time simulation there might be other events coming from other processes
     * with a yet smaller timestamp.
     *
     * This method should not have side effects, except for discarding stale events
     * from the FES.
     */
    virtual cEvent *guessNextEvent() override;

    /**
     * Return the next event to be processed. Normally (with sequential execution),
     * it just returns the first event in the FES. With parallel and/or real-time
     * simulation, it is also the scheduler's task to synchronize with real time
     * and/or with other partitions.
     *
     * If there's no more event, it throws cTerminationException.
     *
     * A nullptr return value means that there's no error but execution
     * was stopped by the user (e.g. with STOP button on the GUI)
     * while takeNextEvent() was waiting for external synchronization.
     */
    virtual cEvent *takeNextEvent() override;

    /**
     * Undo for takeNextEvent(), approximately: if an event was obtained from
     * takeNextEvent() but was not yet processed, it is possible to temporarily
     * put it back to the FES.
     *
     * The scheduler class must guarantee that removing the event via
     * takeNextEvent() again does NOT repeat the side effects of the
     * first takeNextEvent()! That is, the sequence
     *
     * <pre>
     *
     * should be equivalent to a single takeNextEvent() call.
     */
    virtual void putBackEvent(cEvent *event) override;


};

} /* namespace inet */

#endif /* INET_COMMON_VENERIS_EXTERNALCLOCKSCHEDULER_H_ */
