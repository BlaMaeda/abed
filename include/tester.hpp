#ifndef ABED_TESTER_HPP
#define ABED_TESTER_HPP

#include <stdexcept>
#include "classifier.hpp"
#include "dataset.hpp"

//! \todo
//! - Constructor that takes Classifier& and DataSet& and calls
//    the other constructor

namespace abed {

    //! Tester class.
    //
    //! Tester implements functions that,
    //! given a classifier and a
    //! dataset, returns statistics about
    //! how good the predictions of the
    //! classifier are.
    //!
    //! The classifier and the dataset pointers 
    //! can be passed at construction or
    //! setted later.

    class Tester {
    public:
        Tester (Classifier* c, DataSet* ds) : classifier(c), data_set(ds) {
            percentage = -1.0;
            if (!ds->is_labeled()) {
                throw std::domain_error("Every datapoint must be labeled.");
            }
        }
        void resubstitution ();
        //void hold_out (double);
        //void cross_validation (int);
        //void leave_one_out ();
        double get_percentage () { return percentage; }
    private:
        Classifier* classifier;
        DataSet* data_set;
        double percentage;
    };
}

#endif /* ABED_TESTER_HPP */
