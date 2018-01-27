#include <Subsystems/Autonomous.h>
#include <WPILib.h>

using namespace std;
Autonomous::Autonomous() : Subsystem("Drive") {



}

//Function to select autonomous mode based on initial position, field layout, and tasks
int Autonomous::ModeSelect() {

	int startPosition;   //Later incorporate Driver Station read-in once custom dashboard is built
	int tasks;     		//^^^^^^^^^^^^
	string layout = DriverStation::GetInstance().GetGameSpecificMessage();

	char layout1 = layout[0];
	char layout2 = layout[1];
	char layout3 = layout[2];

	//Doesn't work, must figure out
	string layoutChars = to_string(layout2);

	SmartDashboard::PutString("DB/String 5", layout);
	SmartDashboard::PutString("DB/String 6", layoutChars);

	switch (startPosition) {

		case 1:

			switch (tasks) {

				case 0:
					return 0;
					break;


				case 1:
					return 1;
					break;

				case 2:

					if (layout1 == 'R') {

						return 2;

					} else {

						return 3;

					}

					break;

				case 3:

					if (layout2 == 'R') {

						return 4;

					} else {

						return 5;

					}

					break;

				case 4:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 6;

						} else {

							return 7;

						}

					} else {

						if (layout2 == 'R') {

							return 8;

						} else {

							return 9;

						}

					}

					break;

				case 5:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 10;

						} else {

							return 11;

						}

					} else {

						if (layout2 == 'R') {

							return 12;

						} else {

							return 13;

						}

					}

					break;

				case 6:

					if (layout2 == 'R') {

						return 14;

					} else {

						return 15;

					}

					break;

				case 7:

					if (layout1 == 'R') {

						return 16;

					} else {

						return 17;

					}

					break;

				default:

					return 1;

			}

			break;

		case 2:

			switch (tasks) {

				case 0:
					return 0;
					break;


				case 1:
					return 1;
					break;

				case 2:

					if (layout1 == 'R') {

						return 18;

					} else {

						return 19;

					}

					break;

				case 3:

					if (layout2 == 'R') {

						return 20;

					} else {

						return 21;

					}

					break;

				case 4:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 22;

						} else {

							return 23;

						}

					} else {

						if (layout2 == 'R') {

							return 24;

						} else {

							return 25;

						}

					}

					break;

				case 5:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 26;

						} else {

							return 27;

						}

					} else {

						if (layout2 == 'R') {

							return 28;

						} else {

							return 29;

						}

					}

					break;

				case 6:

					if (layout2 == 'R') {

						return 30;

					} else {

						return 31;

					}

					break;

				case 7:

					if (layout1 == 'R') {

						return 32;

					} else {

						return 33;

					}

					break;

				case 8: //Places block in exchange

					return 82;
					break;

				case 9: //Places block in exchange, gets another block, places second block in exchange

					return 83;
					break;

				case 10: //Places block in exchange, gets another block, places second box in switch

					if (layout1 == 'R') {

						return 84;

					} else {

						return 85;

					}

					break;

				case 11: //Places block in exchange, picks up and places two blocks in switch

					if (layout1 == 'R') {

						return 86;

					} else {

						return 87;

					}

				default:

					return 1;

			}

			break;

		case 3:

			switch (tasks) {

				case 0:
					return 0;
					break;


				case 1:
					return 1;
					break;

				case 2:

					if (layout1 == 'R') {

						return 34;

					} else {

						return 35;

					}

					break;

				case 3:

					if (layout2 == 'R') {

						return 36;

					} else {

						return 37;

					}

					break;

				case 4:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 38;

						} else {

							return 39;

						}

					} else {

						if (layout2 == 'R') {

							return 40;

						} else {

							return 41;

						}

					}

					break;

				case 5:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 42;

						} else {

							return 43;

						}

					} else {

						if (layout2 == 'R') {

							return 44;

						} else {

							return 45;

						}

					}

					break;

				case 6:

					if (layout2 == 'R') {

						return 46;

					} else {

						return 47;

					}

					break;

				case 7:

					if (layout1 == 'R') {

						return 48;

					} else {

						return 49;

					}

					break;

				case 8: //Places block in exchange

					return 88;
					break;

				case 9: //Places block in exchange, gets another block, places second block in exchange

					return 89;
					break;

				case 10: //Places block in exchange, gets another block, places second box in switch

					if (layout1 == 'R') {

						return 90;

					} else {

						return 91;

					}

					break;

				case 11: //Places block in exchange, picks up and places two blocks in switch

					if (layout1 == 'R') {

						return 92;

					} else {

						return 93;

					}

				default:

					return 1;

			}

			break;

		case 4:

			switch (tasks) {

				case 0:
					return 0;
					break;


				case 1:
					return 1;
					break;

				case 2:

					if (layout1 == 'R') {

						return 50;

					} else {

						return 51;

					}

					break;

				case 3:

					if (layout2 == 'R') {

						return 52;

					} else {

						return 53;

					}

					break;

				case 4:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 54;

						} else {

							return 55;

						}

					} else {

						if (layout2 == 'R') {

							return 56;

						} else {

							return 57;

						}

					}

					break;

				case 5:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 58;

						} else {

							return 59;

						}

					} else {

						if (layout2 == 'R') {

							return 60;

						} else {

							return 61;

						}

					}

					break;

				case 6:

					if (layout2 == 'R') {

						return 62;

					} else {

						return 63;

					}

					break;

				case 7:

					if (layout1 == 'R') {

						return 64;

					} else {

						return 65;

					}

					break;

				default:

					return 1;

			}

			break;

		case 5:

			switch (tasks) {

				case 0:
					return 0;
					break;


				case 1:
					return 1;
					break;

				case 2:

					if (layout1 == 'R') {

						return 66;

					} else {

						return 67;

					}

					break;

				case 3:

					if (layout2 == 'R') {

						return 68;

					} else {

						return 69;

					}

					break;

				case 4:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 70;

						} else {

							return 71;

						}

					} else {

						if (layout2 == 'R') {

							return 72;

						} else {

							return 73;

						}

					}

					break;

				case 5:

					if (layout1 == 'R') {

						if (layout2 == 'R') {

							return 74;

						} else {

							return 75;

						}

					} else {

						if (layout2 == 'R') {

							return 76;

						} else {

							return 77;

						}

					}

					break;

				case 6:

					if (layout2 == 'R') {

						return 78;

					} else {

						return 79;

					}

					break;

				case 7:

					if (layout1 == 'R') {

						return 80;

					} else {

						return 81;

					}

					break;

				default:

					return 1;

			}

			break;

		default:

			return 1;

	}


}


