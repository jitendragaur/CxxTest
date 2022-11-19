import CxxTest

public struct CxxInterop {

        
    func test() {
        var acceleration: [CDouble] = [ 1, 2, 3, 4, 5 ]
        var gravity: [CDouble] = [ 1, 2, 3, 4, 5 ]
        var attitude: [CDouble] = [ 1, 2, 3, 4, 5 ]
        var time: [CDouble] = [ 1, 2, 3, 4, 5 ]
        
        var calculator = VelocityCalculator(&acceleration, &gravity, &attitude, &time, CInt(time.count))
        
        let result = calculator.calculate()
        
        print("Did calculation fail: \(result.getCalculationFailedStatus())")
        
        let numberOfReps = Int(result.getNumberOfReps())
        
        let loweringPtr = UnsafeMutablePointer<CDouble>.allocate(capacity: numberOfReps)
        let raisingPtr = UnsafeMutablePointer<CDouble>.allocate(capacity: numberOfReps)
        
        result.getLoweringVelocities(loweringPtr)
        result.getRaisingVelocities(raisingPtr)
        
        let loweringBuffer = UnsafeBufferPointer(start: loweringPtr, count: numberOfReps)
        let raisingBuffer = UnsafeBufferPointer(start: raisingPtr, count: numberOfReps)
        
        let loweringVelocities = Array(loweringBuffer)
        let raisingVelocities = Array(raisingBuffer)
        
        print(loweringVelocities)
        print(raisingVelocities)
    }
}



