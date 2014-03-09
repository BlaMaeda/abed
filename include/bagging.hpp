#ifndef ABED_BAGGING_HPP
#define ABED_BAGGING_HPP

#include <cassert>
#include "ensemble.hpp"

namespace abed {

    class Bagging : public EnsembleClassifier {
    public:
        Bagging (int c) : no_classes(c) {}
        virtual void initialize (unsigned int seed = UINT_MAX);

        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual double train (const DynamicDataSet&,
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);

        virtual unsigned int predict_label (const StaticDataPoint&) const;
        virtual unsigned int predict_label (const DynamicDataPoint&) const;

    private:
        unsigned int no_classes;
    };

}

#endif /* ABED_BAGGING_HPP */

