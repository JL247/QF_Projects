//main() handles subsytem startup and slave connection
int main(int argc, _TCHAR* argv[])
{
		// Only continue once the subsystem is started and connected to EtherCat
		while (!StartKingstar()) {
			Sleep(5000);
			StartKingstar();
		}

		GetStatus(&Subsystem, NULL);

		// If we're connected to EtherCat devices, then setup the timers to schedule the signal processing
		if (Subsystem.State > 1) {

			RtSetThreadPriority(GetCurrentThread(), RT_PRIORITY_MAX);

			HANDLE timerhandle;
			timerhandle = RtCreateTimer(
				NULL,
				0,
				EcSignalProcessing,
				timerhandle,
				RT_PRIORITY_MAX,
				CLOCK_FASTEST
			);

			if (timerhandle != NULL) {
				std::cout << " Successfully Created RTX Timer " << std::endl;
			}
			else {
				std::cout << " Failed to get RTX Timer " << std::endl;
			}

			LARGE_INTEGER timerInterval;
			LARGE_INTEGER timerExpiry;

			timerInterval.QuadPart = 250 * 10;	//described in 100 nanosecond units, thus 250 microseconds
			timerExpiry.QuadPart = 250 * 10;

			BOOL setTimerInteral = RtSetTimerRelative(
				timerhandle,
				&timerExpiry,
				&timerInterval
			);
			if (setTimerInteral) {
				std::cout << " Successfully Set RTX Timer Interval: " << timerInterval.QuadPart << "\n" << std::endl;
			}

			// Run forever.
			for (;;)
				SuspendThread(GetCurrentThread());
		}

		// The master initially reads dyno status information**
		// Information about the dyno is grouped into index adresses (e.g. 0x1A00 is a read address from Unico), each address contains collections of bits (words) which tell some info about the dyno
		// To send dyno status info to dSPACE, we can use "ReadOutputWord" a ksapi funciton. We need to state which slave to read from, then the word offset so we read the correct sequence of bits,
		// for example if the entire Unico-->HostDevice message (which contains various info about the dyno) consists of 512 bits (32 words), and the status flag info is the fourth set of 16 bits (the fourth word)
		// then we use this function to read all 16 bits starting from the offset posisiton.

	/* 		if(!setMonitorEvents()){
				std::cout << "Failed to setup monitoring events, monitoring setup skipped" << std::endl;
			}
			else{
				std::cout << "Successfully setup all monitoring events" << std::endl;
				if(!RtMonitorControl(MONITOR_CONTROL_START, NULL, NULL)){
					handleError();	//get the error code if start monitor fails
					std::cout << "Failed to start the monitoring session" << std::endl;
				}
				else{
					std::cout << "Starting the monitoring session" << std::endl;
				}
			} */
}