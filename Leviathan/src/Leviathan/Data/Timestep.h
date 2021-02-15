#pragma once
class Timestep {
public:
    Timestep(float step = 0.0f) : s_time(step) {}

    operator int() const { return int(s_time); }
    operator float() const { return s_time; }
    operator double() const { return double(s_time); }

    inline float GetSeconds() { return this->s_time; }
    inline float GetMiliseconds() { return this->s_time * 1000.0f; }

    void SetTimestep(int step) { this->s_time = float(step); }
    void SetTimestep(float step) { this->s_time = step; }
    void SetTimestep(double step) { this->s_time = float(step); }

    static Timestep Calculate(int begin, int end) { return Timestep(float(end - begin)); }
    static Timestep Calculate(float begin, float end) { return Timestep(end - begin); }
    static Timestep Calculate(double begin, double end) { return Timestep(float(end - begin)); }
private:
    float s_time;
};