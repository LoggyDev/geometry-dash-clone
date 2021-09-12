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


