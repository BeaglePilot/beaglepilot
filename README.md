BeaglePilot:
=============

An autopilot for Linux-based computers based on the BeagleBone (Black).

| Timeline | Anuj Deshpande| Siddharth Bharat Purohit| Víctor Mayoral Vilches |
|----------|-------------- |-------------------------|------------------------|
| **Community Bonding** (21st April - 19th May 4 weeks)| | Coding started and trying to pull the timeline as up as possible leaving voids to do more :)| Already started coding and the discussion at #beaglepilot (Freenode). The mentors provided great feedback and tutorials to get started. The goal will be to get familiar with ArduPilot and start coding drivers (userspace ones at the beginning) for the hardware to be used (PixHawk Fire Cape). |
| May 19th - May 25th | | use beaglebone pru driver lib to upload firmware using remotproc| Hardware drivers coding (userspace) over the ArduPilot code (Linux kernel with RT_PREEMPT patches applied). |
| May 26th - June 1st | | Create data handling library for PRU0, PRU1 and ARM| Hardware drivers coding. |
| June 2nd - June 8th | | " | Code of hw tests. Make sure that all the hardware interfaces properly.| 
| June 9th - June 15th | | Port Starterware Library to PRU| Realtime comparison: stock kernel userspace vs RT_PREEMPT kernel userspace (desirable to include tests with Xenomai if the time allows it) |
| June 16th - July 22nd | | "| ROS integration through MAVLink (using mavlink_ros ROS package). This first task is expected to be straightforward.|
| June 23rd - June 29th | | "| (**Midterm Eval**) ROS bridge coded directly in the ArduPilot code as an optional module. |
| June 30th - July 6th | |Create driver library (along with firmware) for Pixhawk Firecape sensors(PRU side) | ROS bridge coded directly in the ArduPilot code as an optional module.|
| July 7th - July 13th | | "| ROS-Ardupilot tests. |
| July 14th - July 20th | | Create driver library for Pixhawk Firecape sensors(ARM side) i.e. Ardupilot AP_HAL compatible| IDE integration, web programming. Probably Codiad or Cloud9 (http://erlerobot.com/blog/programming-a-flying-robot-in-the-browser/). |
| July 21st - July 27th | |Intensive testing of Pixhawk Firecape with Ardupilot ported | Security review of Ardupilot running on a RT_PREEMPT patched kernel.|
| July 28th - August 3rd | | Final housekeeping| Security issues. |
| August 4th - August 10th | |Live Test and Documentation | Overall review an tutorials development. |
| August 11th - August 18th | |Live Test and Documentation | Wrap-up, documentation and delivery. |

Test Platforms:
==============
BeaglePilot is currently being tested using the following drones:
- [Erle Robot](http://erlerobot.com)

Contributors:
=============

- Víctor Mayoral Vilches <v.mayoralv@gmail.com>
- Anuj Deshpande <anujdeshpande92@gmail.com>
- Siddharth Bharat Purohit <sidbpurohit@gmail.com>
- Mitul Vekariya <vekariya93@gmail.com>

Communication:
==============
- IRC Freenode #beaglepilot ([logs](http://logs.nslu2-linux.org/livelogs/beaglepilot/))
- [BeaglePilot mailing list](https://groups.google.com/forum/#!forum/beaglepilot)

[![Visit our IRC channel](https://kiwiirc.com/buttons/chat.freenode.net/beaglepilot.png)](https://kiwiirc.com/client/chat.freenode.net/?nick=beaglepilo|?#beaglepilot)
