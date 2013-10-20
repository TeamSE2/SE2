
#ifndef MOTOR
#define MOTOR

namespace HAL{
	class Motor{
	private:
		static Motor *instance;
		Motor();
	public:
		~Motor();
		static Motor* getInstance();
		void motorRechtsLauf();
		void motorLinksLauf();
		void motorLangsam();
		void motorSchnell();
		void motorStop();
		void motorStart();

	};
}

#endif
