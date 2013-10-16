#ifndef WEICHE
#define WEICHE

namespace HAL{

	class Weiche{
	private:
		static Weiche *instance;
		Weiche();

	public:
		~Weiche();
		static Weiche* getInstance();
		void weicheAuf();
		void weicheZu();

	};
}

#endif
