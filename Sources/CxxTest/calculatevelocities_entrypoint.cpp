#include "calculatevelocities_entrypoint.h"
#include "calculatevelocities.h"

coder::array<double, 2U> init_sensor_array(const std::vector<double> source)
{
    coder::array<double, 2U> result;
    result.set_size(3, source.size() / 3);

    for (int i = 0; i < source.size(); i++)
    {
        result[i] = source[i];
    }

    return result;
}

coder::array<double, 2U> init_time_array(const std::vector<double> source)
{
    coder::array<double, 2U> result;
    result.set_size(1, source.size());

    for (int i = 0; i < source.size(); i++)
    {
        result[i] = source[i];
    }

    return result;
}

VelocityCalculationResult calculatevelocities_entrypoint(
    const std::vector<double> acceleration,
    std::vector<double> gravity,
    const std::vector<double> attitude,
    std::vector<double> time)
{
    auto internal_acceleration = init_sensor_array(acceleration);
    auto internal_gravity = init_sensor_array(gravity);
    auto internal_attitude = init_sensor_array(attitude);
    auto internal_time = init_time_array(time);

    struct0_T v_out;
    double reps_out = 0;

    calculatevelocities(internal_acceleration, internal_gravity, internal_attitude, internal_time, &v_out, &reps_out);

    int numberOfReps = int(reps_out);
    std::vector<double> loweringVelocities;
    std::vector<double> raisingVelocities;

    for (int i = 0; i < numberOfReps; i++)
    {
        loweringVelocities.push_back(v_out.V_lowering[i]);
        raisingVelocities.push_back(v_out.V_raising[i]);
    }

    VelocityCalculationResult result(numberOfReps, loweringVelocities, raisingVelocities);
    return result;
}


VelocityCalculationResult::VelocityCalculationResult()
{
    this->didCalculationFail = true;
    this->numberOfReps = -1;
    this->loweringVelocities = std::vector<double>();
    this->raisingVelocities = std::vector<double>();
}

VelocityCalculationResult::VelocityCalculationResult(
    int numberOfReps,
    std::vector<double> loweringVelocities,
    std::vector<double> raisingVelocities)
{
    this->didCalculationFail = false;
    this->numberOfReps = numberOfReps;
    this->loweringVelocities = loweringVelocities;
    this->raisingVelocities = raisingVelocities;
}

VelocityCalculationResult VelocityCalculator::calculate()
{
    try {
        return calculatevelocities_entrypoint(this->acceleration, this->gravity, this->attitude, this->time);
    }
    catch (...) {
        VelocityCalculationResult result;
        return result;
    }
}

const int VelocityCalculationResult::getNumberOfReps() const
{
    return this->numberOfReps;
}

const void VelocityCalculationResult::getLoweringVelocities(double* velocities) const
{
    for (int i = 0; i < this->loweringVelocities.size(); i++) {
        velocities[i] = this->loweringVelocities[i];
    }
}

const void VelocityCalculationResult::getRaisingVelocities(double* velocities) const
{
    for (int i = 0; i < this->raisingVelocities.size(); i++) {
        velocities[i] = this->raisingVelocities[i];
    }
}

const bool VelocityCalculationResult::getCalculationFailedStatus() const
{
    return this->didCalculationFail;
}

VelocityCalculator::VelocityCalculator(
    double* acceleration,
    double* gravity,
    double* attitude,
    double* time,
    int numberOfReadings)
{
    for (int i = 0; i < numberOfReadings * 3; i++) {
        this->acceleration.push_back(acceleration[i]);
        this->gravity.push_back(gravity[i]);
        this->attitude.push_back(attitude[i]);
    }

    for (int i = 0; i < numberOfReadings; i++) {
        this->time.push_back(time[i]);
    }
}
