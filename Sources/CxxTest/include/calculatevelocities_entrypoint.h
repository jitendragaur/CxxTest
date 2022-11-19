//
//  calculatevelocities_entrypoint.h
//  CalculateVelocitiesApp
//
//  Created by Odei Bretón on 09/11/2022.
//

#ifndef calculatevelocities_entrypoint_h
#define calculatevelocities_entrypoint_h

#include <vector>

class VelocityCalculationResult {
    bool didCalculationFail;
    int numberOfReps;
    std::vector<double> loweringVelocities;
    std::vector<double> raisingVelocities;

public:
    VelocityCalculationResult();
    VelocityCalculationResult(int numberOfReps, std::vector<double> velocityLowering, std::vector<double> velocityRaising);
    const int getNumberOfReps() const;
    const void getLoweringVelocities(double* velocities) const;
    const void getRaisingVelocities(double* velocities) const;
    const bool getCalculationFailedStatus() const;
};

class VelocityCalculator {
    std::vector<double> acceleration;
    std::vector<double> gravity;
    std::vector<double> attitude;
    std::vector<double> time;

public:
    VelocityCalculator(
        double* acceleration,
        double* gravity,
        double* attitude,
        double* time,
        int numberOfReadings);

    VelocityCalculationResult calculate();
};

VelocityCalculationResult calculatevelocities_entrypoint(
    const std::vector<double> acceleration,
    std::vector<double> gravity,
    const std::vector<double> attitude,
    std::vector<double> time);

#endif /* calculatevelocities_entrypoint_h */
