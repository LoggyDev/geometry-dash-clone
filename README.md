![Untitled](https://user-images.githubusercontent.com/60048714/133001167-b4b3ead2-9b9e-4c0d-bf3a-d5038b73b05b.png)
# geometry-dash-clone
this was coded in c++, all assets are by me.
credit: 
lerp: https://www.gmlscripts.com/script/lerp (converted to c++ by me)
approach: https://github.com/thelucre/gamemaker-scripts/blob/master/Approach.gml (converted to c++ by me)

float lerp (float a, float b, float f) {
    return (a * (1.0f - f)) + (b * f);
}

double approach(double a, double b, double c) {
	if (a < b) return std::min(a + c, b); else return std::max(a - c, b);
}

![Untitled](https://user-images.githubusercontent.com/60048714/133000404-f7cc83af-3191-4224-9328-db9ea5daac9c.png)

