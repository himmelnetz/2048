
#ifndef ___STATISTICS__H___
#define ___STATISTICS__H___

#include <vector>

using std::vector;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Summary_Statistics {

private:

	vector<double> data;

public:

	Summary_Statistics();
	~Summary_Statistics();

	void add_datum(double datum);
	void add_data(double* data, int n);
	void add_data(vector<double> data);

	int get_n();
	double get_mean();
	double get_stdev();
	double get_skew();
	double get_kurtosis();

	double get_median();

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* ___STATISTICS__H___ */
