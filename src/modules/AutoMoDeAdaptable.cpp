/**
 * @file <src/modules/AutoMoDeAdaptable.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */
/****************************************/
/****************************************/

template <typename T>
void AutoMoDeAdaptable<T>::Init(UInt32 evaluationSteps, T value) {
    m_uEvaluationTime = evaluationSteps;
    m_uEvaluationStep = 0;
    m_tPossibleValues.clear();
    m_tPossibleValues.push_back(value);
    m_fRewards.clear();
    m_fRewards.push_back(0);
    m_iPulls.clear();
    m_iPulls.push_back(0);
}

/****************************************/
/****************************************/

template <typename T>
void AutoMoDeAdaptable<T>::Init(UInt32 evaluationSteps, std::vector<T> possibleValues) {
    m_uEvaluationTime = evaluationSteps;
    m_uEvaluationStep = 0;
    m_tPossibleValues = std::vector<T>(possibleValues);
    m_fRewards = std::vector<Real>(possibleValues.size(), 0);
    m_iPulls = std::vector<SInt32>(possibleValues.size(), 0);
}

/****************************************/
/****************************************/

template <typename T>
AutoMoDeAdaptable<T>::operator T() const {
    return m_tPossibleValues[m_iIndex];
}

/****************************************/
/****************************************/

template <typename T>
AutoMoDeAdaptable<T> AutoMoDeAdaptable<T>::Clone(const AutoMoDeAdaptable<T>& origin) {
    auto instance = AutoMoDeAdaptable<T>();

    instance.m_uEvaluationTime = origin.m_uEvaluationTime;
    instance.m_uEvaluationStep = origin.m_uEvaluationStep;
    instance.m_iIndex = origin.m_iIndex;
    instance.m_tPossibleValues = origin.m_tPossibleValues;
    instance.m_fRewards = origin.m_fRewards;
    instance.m_iPulls = origin.m_iPulls;

    return instance;
}

/****************************************/
/****************************************/

template <typename T>
void AutoMoDeAdaptable<T>::Adapt(Real reward) {
    // update the reward of the current arm (i.e., parameter)
    m_fRewards[m_iIndex] += reward;

    // if the evaluation epoch terminated, start a new one
    if (++m_uEvaluationStep >= m_uEvaluationTime && m_tPossibleValues.size() > 1) {
        m_uEvaluationStep = 0;
        m_iPulls[m_iIndex]++;
        m_iIndex = AutoMoDeAdaptable<T>::SelectArm();
    }
}

/****************************************/
/****************************************/

template <typename T>
SInt32 AutoMoDeAdaptable<T>::SelectArm() {
    // accumulator variable for the total number of rounds
    SInt32 pullsCount = 0;

    // counts the total number of rounds
    for (SInt32 pull : m_iPulls) {
        pullsCount += pull;
    }

    // the calculation of the confidence radius considers
    // the same nominator for all the arms
    Real nominator = 2 * log(pullsCount);

    // setup auxiliary variables to find the arm to pull
    Real max = 0;
    SInt32 maxIdx = -1;

    // find the arm with the larger UCB or the first untested one
    for (long unsigned int i = 0; i < m_tPossibleValues.size(); i++) {
        // the default setting for any arm is max range (i.e., unknown)
        Real mu = 0;
        Real r = std::numeric_limits<Real>::max();

        // if an arm has been tried before override the default priority
        if (m_iPulls[i] > 0) {
            mu = m_fRewards[i] / m_iPulls[i];
            r = sqrt(nominator / m_iPulls[i]);
        }

        // if the arm “i” is more worth trying, select it
        if (mu + r > max) {
            max = mu + r;
            maxIdx = i;
        }
    }

    return maxIdx;
}
