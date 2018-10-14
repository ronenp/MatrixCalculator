/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include <fstream>

#include <cmath>
#include <string>
#include <set>
 
using namespace std;

class rational {
public:
	rational() {}

	long long int num=0, denom=1;
};

void print_matrix(long long int rows, long long int columns, vector<vector<rational>>& matrix) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cout << matrix[i][j].num << '\t';
		}
		cout << '\n';
	}
}

long long int find_lcm(rational r1, rational r2) {

	long long int a = std::abs(r1.num);
	long long int b = std::abs(r2.num);

	long long int maxVal;
	maxVal = (a > b) ? a : b;


	while (true) {
		if ((maxVal%a == 0) && (maxVal%b == 0)) {
			return maxVal;
		}
		++maxVal;
	}
	
}

rational simplify_fraction(rational r) {
	long long int i = std::abs(r.num) < std::abs(r.denom) ? std::abs(r.num) : std::abs(r.denom);
	for (; i >= 2; i--) {
		if (r.num%i == 0 && r.denom%i == 0) {
			r.num = r.num / i;
			r.denom = r.denom / i;
		}
	}
	return r;
}

void calculate_matrix(long long int rows, long long int columns, vector<vector<rational>>& matrix) {
	
	const int empty = 0;
	int first_row = 0;
	for (int i = 0; i < columns-1; ++i) { // columns-1 because last column is b
		for (int current_row = first_row; current_row < rows; ) {
			if (matrix[current_row][i].num != empty) {
				if (current_row != first_row) {
					std::swap(matrix[current_row], matrix[first_row]);
					
				}
				for (;;) {
					
					if (current_row < rows) {
						for (int k = current_row + 1; k < rows; ++k) {
							if (matrix[k][i].num != empty) {
								//calculate
								long long int lcm = find_lcm(matrix[first_row][i], matrix[k][i]);

								vector<rational> first_row_copy = matrix[first_row];
								if (lcm == matrix[first_row][i].num) {
									if (lcm == matrix[k][i].num) {
										//subtract regularaly
									}
									else {
										long long int second_row_multiple = std::abs(lcm/matrix[k][i].num);

										//multiply only the second row
										for (int m = 0; m < matrix[k].size(); ++m) {
											matrix[k][m].num *= second_row_multiple;
										}
									}
								}
								else if (lcm == matrix[k][i].num) {
									long long int first_row_multiple = std::abs(lcm/matrix[first_row][i].num);
									//multiply first row 

									for (int m = 0; m < first_row_copy.size(); ++m) {
										first_row_copy[m].num *= first_row_multiple;
									}
								}
								else {

									long long int first_row_multiple = std::abs(lcm/matrix[first_row][i].num );
									long long int second_row_multiple = std::abs(lcm/matrix[k][i].num );

									for (int m = 0; m < first_row_copy.size(); ++m) {
										first_row_copy[m].num *= first_row_multiple;
									}

									for (int m = 0; m < matrix[k].size(); ++m) {
										matrix[k][m].num *= second_row_multiple;
									}
								}


								//subtract
								if ((first_row_copy[i].num > 0 && matrix[k][i].num > 0) || (first_row_copy[i].num < 0 && matrix[k][i].num < 0)) {
									for (int m =i; m < matrix[k].size(); ++m) {
										matrix[k][m].num -= first_row_copy[m].num;
									}
								}
								else {
									for (int m = i; m < matrix[k].size(); ++m) {
										matrix[k][m].num += first_row_copy[m].num;
									}
								}

								//cout << "\n\n";
								//print_matrix(rows, columns, matrix);

								++current_row;
							}
							else {
								++current_row;
								continue;
							}
						}
						++current_row;
					}
					else {
						for (int p = first_row - 1; p >= 0; --p) {
							if (matrix[p][i].num != empty) {
								//calculate
								long long int lcm = find_lcm(matrix[first_row][i], matrix[p][i]);

								vector<rational> first_row_copy = matrix[first_row];
								if (lcm == matrix[first_row][i].num) {
									if (lcm == matrix[p][i].num) {
										//subtract regularaly
									}
									else {
										long long int second_row_multiple = std::abs(lcm/matrix[p][i].num );

										//multiply only the second row 
										for (int m = 0; m < matrix[p].size(); ++m) {
											matrix[p][m].num *= second_row_multiple;
										}
									}
								}
								else if (lcm == matrix[p][i].num) {
									long long int first_row_multiple = std::abs(lcm/matrix[first_row][i].num );
									//multiply first row 

									for (int m = 0; m < first_row_copy.size(); ++m) {
										first_row_copy[m].num *= first_row_multiple;
									}
								}
								else {
									long long int first_row_multiple = std::abs(lcm/matrix[first_row][i].num );
									long long int second_row_multiple = std::abs(lcm/matrix[p][i].num );

									for (int m = 0; m < first_row_copy.size(); ++m) {
										first_row_copy[m].num *= first_row_multiple;
									}

									for (int m = 0; m < matrix[p].size(); ++m) {
										matrix[p][m].num *= second_row_multiple;
									}
								}

								if ((first_row_copy[i].num > 0 && matrix[p][i].num > 0) || (first_row_copy[i].num < 0 && matrix[p][i].num < 0)) {
									for (int m = i; m < matrix[p].size(); ++m) {
										matrix[p][m].num -= first_row_copy[m].num;
									}
								}
								else {
									for (int m = i; m < matrix[p].size(); ++m) {
										matrix[p][m].num += first_row_copy[m].num;
									}
								}


								//cout << "\n\n";
								//print_matrix(rows, columns, matrix);

							}
							else {
								continue;
							}
						}
						++first_row;
						
						break;// we are done with that column
					}

				}
				break;
			}
			else {
				++current_row;
				continue;
			}
		} // end of row for
		
	} // end of column for

}

bool check_for_inconsistent(long long int rows, long long int columns, vector<vector<rational>>& matrix) {
	const int empty = 0;
	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < columns; ++i) {
			if (i < columns - 1) {
				if (matrix[j][i].num != empty) {
					break;
				}
			}
			else if(matrix[j][i].num!=empty) {
				cout << "the system is inconsistent;\n";
				return true;

			}
		}
	}
	return false;
}

void print_solution(long long int rows, long long int columns, vector<vector<rational>>& matrix) {
	long long int divisor = 1;
	const int empty = 0;
	bool first = false;
	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < columns; ++i) {
			if (matrix[j][i].num != empty&&first==false) {

				divisor = matrix[j][i].num;
				if (divisor < 0) {
					matrix[j][i].num /= divisor;
				}
				else {
					matrix[j][i].num /= divisor;
				}
				first = true;
			}
			else if(matrix[j][i].num != empty&&first==true){
				if (divisor < 0) {
					matrix[j][i].num = -matrix[j][i].num;
					matrix[j][i].denom *= (-divisor);
				}
				else {
					matrix[j][i].denom *= divisor;
				}
			}
		}
		first = false;
	}

	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < columns; ++i) {
			matrix[j][i] = simplify_fraction(matrix[j][i]);
		}
	}

	std::set<int> free_variables;

	cout << "\n\n";
	//print_matrix(rows, columns, matrix);

	for (int i = 0; i < columns - 1; ++i) {
		free_variables.insert(i + 1);
	}

	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < columns-1; ++i) {
			
			if (matrix[j][i].num != empty) {
				
				free_variables.erase(i+1);
				cout << "X" << i + 1 << " = ";
				if (matrix[j][columns - 1].num == 0) {
					cout << "0";
				}
				else {
					cout << matrix[j][columns - 1].num;
				}

				if (matrix[j][columns - 1].denom != 1)cout << "/" << matrix[j][columns - 1].denom << " ";
				else cout << " ";
				
				for (int k = i+1; k < columns - 1; ++k) {
					if (matrix[j][k].num > 0) {

						 
						cout << " (" << -matrix[j][k].num;
						if (matrix[j][k].denom != 1)cout << "/" << matrix[j][k].denom << ")X"<<k+1<<" ";
						else cout <<")X"<<k+1 <<" ";
					}
					else if (matrix[j][k].num < 0) {
					 
						cout << "+ (" << -matrix[j][k].num;
						if (matrix[j][k].denom != 1)cout << "/" << matrix[j][k].denom << ")X"<<k+1<<" ";
						else cout << ")X" << k+1<< " ";
					}
				}
				cout << '\n';
				break;
			}
			
		} // columns loop
	} // rows loop

 

	//print free_variables:
	if (free_variables.empty()) {
		return;
	}
	else {
		cout << "\nfree: ";
		for (auto it = free_variables.begin(); it != free_variables.end(); ++it) {
			cout << "X" << *it << ", ";
		}
		cout << '\n';
	}
}

int main (int argc, char* argv[])
{
	
 

	cout << "Enter rows: ";
	int rows = 0;
	cin >> rows;
	cout << "Enter columns (including b): ";
	int columns = 0;
	cin >> columns;

	vector<vector<rational>> matrix(rows);


	cout << "Enter matrix text file name: ";
	std::string filename;
	cin >> filename;

	ifstream ifs;
	ifs.open(filename);
	if (ifs.is_open()) {
		int n;
		int i = 0;
		int j = 0;
		while (ifs >> n) {
			rational r;
			r.num = n;
			matrix[j].push_back(r);
			++i;
			if (i >= columns) { 
				i = 0;
				++j;
			}
			if (j >= rows)break;
		}		

		print_matrix(rows, columns, matrix);

		calculate_matrix(rows, columns, matrix);
		bool inconsistent = check_for_inconsistent(rows, columns, matrix);
		if (inconsistent)return 0;


		print_solution(rows, columns, matrix);

		ifs.close();
	}
	else {
		cout << "cannot open the file;";
	}
	
 



    return 0;
}
