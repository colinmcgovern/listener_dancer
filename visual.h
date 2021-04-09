#ifndef VISUAL_H
#define VISUAL_H

class visual{
	private:
		double x = 0, y = 0, z = 0;

	public:
		void update_rotation(double x_, double y_, double z_);
		void start();
};

#endif