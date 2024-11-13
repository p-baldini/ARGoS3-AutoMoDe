/**
 * @file <src/modules/AutoMoDeAdaptable.cpp>
 * 
 * @author Paolo Baldini - <paolo.baldini.phd@gmail.com>
 * 
 * @package ARGoS3-AutoMoDe
 * 
 * @license MIT License
 */

/**
 * Selects the arm to pull according to the rewards obtained and the number of pulls.
 * Implementation of the UCB1 algorithm. This function is visible only in the current file.
 * 
 * @param[in] rewards The cumulative reward obtained by each arm.
 * @param[in] pulls The number of time each arm has been tried.
 * @param[in] arms_count The total number of possible arms.
 * @return The index of the arm (or value) selected to be used next.
 */
static SInt32 SelectArm(
    const std::vector<Real> rewards,
    const std::vector<SInt32> pulls,
    int arms_count
) {
    // accumulator variable for the total number of rounds
    SInt32 pulls_count = 0;

    // counts the total number of rounds
    for (SInt32 pull : pulls) {
        pulls_count += pull;
    }

    // the calculation of the confidence radius considers
    // the same nominator for all the arms
    Real nominator = 2 * log(pulls_count);

    // setup auxiliary variables to find the arm to pull
    Real max = 0;
    SInt32 max_idx = -1;

    // find the arm with the larger UCB
    for (SInt32 i = 0; i < arms_count; i++) {
        Real mu = rewards[i] / pulls[i];
        Real r = sqrt(nominator / pulls[i]);

        // if the arm “i” is more worth trying, select it
        if (mu + r > max) {
            max = mu + r;
            max_idx = i;
        }
    }

    return max_idx;
}

/****************************************/
/****************************************/

template <typename T>
void AutoMoDeAdaptable<T>::Init(T value) {
    m_tPossibleValues.clear();
    m_tPossibleValues.push_back(value);
    m_fRewards.clear();
    m_fRewards.push_back(1);
    m_iPulls.clear();
    m_iPulls.push_back(1);
}

/****************************************/
/****************************************/

template <typename T>
void AutoMoDeAdaptable<T>::Init(std::vector<T> possibleValues) {
    m_tPossibleValues = std::vector<T>(possibleValues);
    m_fRewards = std::vector<Real>(possibleValues.size(), 1);
    m_iPulls = std::vector<SInt32>(possibleValues.size(), 1);
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
    if (m_tPossibleValues.size() > 1) {
        m_fRewards[m_iIndex] += reward;
        m_iPulls[m_iIndex]++;
        m_iIndex = SelectArm(m_fRewards, m_iPulls, m_tPossibleValues.size());
    }
}
