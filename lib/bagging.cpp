#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cassert>
#include "../include/bagging.hpp"

namespace abed {
    using std::vector;

    void Bagging::initialize (unsigned int seed) {
        if (seed != UINT_MAX) {
            srand(seed);
        }
        
        for (unsigned int i = 0; i < classifiers.size(); i++) {
            classifiers[i]->initialize();
        }
    }

    double Bagging::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        if (sds.get_dimension() != this->dimension) {
            throw std::domain_error("Dimension of Bagging and dataset are not the same");
        }
        if (sds.get_no_classes() != this->no_classes) {
            throw std::domain_error("Number of classes of Bagging and dataset are not the same");
        }

        double mean_train_error = 0.0;
        for (unsigned int i = 0; i < classifiers.size(); i++) {
            DataSet* bootstrapped = sds.bootstrap();
            
            mean_train_error += classifiers[i]->train(bootstrapped, MAX_ERROR, MAX_IT);

            delete bootstrapped;
        }
        mean_train_error /= classifiers.size();
        return mean_train_error;
    }

    // TODO SOOO MUCH REPETITION
    double Bagging::train (const DynamicDataSet& dds, double MAX_ERROR, unsigned int MAX_IT) {
        double mean_train_error = 0.0;
        for (unsigned int i = 0; i < classifiers.size(); i++) {
            DataSet* bootstrapped = dds.bootstrap();
            
            mean_train_error += classifiers[i]->train(bootstrapped, MAX_ERROR, MAX_IT);

            delete bootstrapped;
        }
        mean_train_error /= classifiers.size();
        return mean_train_error;
    }

    unsigned int Bagging::predict_label (const StaticDataPoint& sdp) const {
        vector<unsigned int> votes(no_classes, 0);

        for (unsigned int i = 0; i < classifiers.size(); i++) {
            unsigned int vote = classifiers[i]->predict_label(sdp);
            assert(vote >= 0 && vote < no_classes);
            votes[vote]++;
        }

        vector<unsigned int>::iterator voted = std::max_element(votes.begin(), votes.end());
        return voted - votes.begin();
    }
    
    unsigned int Bagging::predict_label (const DynamicDataPoint& ddp) const {
        vector<unsigned int> votes(no_classes, 0);

        for (unsigned int i = 0; i < classifiers.size(); i++) {
            unsigned int vote = classifiers[i]->predict_label(ddp);
            votes[vote]++;
        }

        vector<unsigned int>::iterator voted = std::max_element(votes.begin(), votes.end());
        return voted - votes.begin();
    }
} // namespace abed
