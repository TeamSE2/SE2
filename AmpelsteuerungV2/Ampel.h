
#ifndef AMPEL
#define AMPEL

namespace HAL{

	class Ampel{
		private:
			static Ampel *instance;
			Ampel();
		public:
			~Ampel();
			static Ampel* getInstance();
			void lampeRotAn();
			void lampeGelbAn();
			void lampeGruenAn();
			void lampeRotAus();
			void lampeGelbAus();
			void lampeGruenAus();
	};
}

#endif
