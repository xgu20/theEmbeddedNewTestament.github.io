enum RollerCoasterType
{
    Wood,
    Steel,
    Suspended,
};

enum LiftType
{
    Chain,
    Cabin,
};

class RollerCoasterPointsCalculator
{
public:
    virtual float BasicScore(LiftType lift, int mile)=0;
    static RollerCoasterPointsCalculator* Create(RollerCoasterPointsCalculator air);
    virtual ~RollerCoasterPointsCalculator() = default;
protected:
    RollerCoasterPointsCalculator() = default;
    int BumpersPerSecond;
    int MaxSpeed;
};

