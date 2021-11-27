#include "sp_Utils.hpp"

struct Matrix{
	int rows;
	int cols;
	double *cp;

	Matrix(): cp(NULL) {}
	Matrix(const u16 numberOfRows, const u16 numberOfColumns, double *const arrayPointer): rows(numberOfRows), cols(numberOfColumns),
		cp(arrayPointer) {}
	Matrix(const u16 numberOfRows, const u16 numberOfColumns): rows(numberOfRows), cols(numberOfColumns){
		cp = new double[numberOfRows*numberOfColumns];
	}
	Matrix(const Matrix &A): rows(A.rows), cols(A.cols), cp(A.cp) {}
	Matrix &operator =(const Matrix &A){
		delete[] cp;
		rows = A.rows;
		cols = A.cols;
		cp = A.cp;
		return *this;
	}
	void free(){
		delete[] cp;
	}
	Matrix &copy(const Matrix &A){
		delete[] cp;
		u16 totalSize = A.rows*A.cols;
		cp = new double[totalSize];
		for(u16 i=0; i<totalSize; i++)
			cp[i] = A.cp[i];
		return *this;
	}
	Matrix make_copy(){
		Matrix M(rows, cols);
		u16 totalSize = rows*cols;
		for(u16 i=0; i<totalSize; i++)
			M.cp[i] = cp[i];
		return M;
	}

	
	double &operator [](const u16 index){
		return cp[index];
	}
	double &operator ()(const u16 row, const u16 column){
		return cp[row*this->cols+column];
	}
	Matrix &shrink(const u16 numberOfRows, const u16 numberOfColumns){
		if(rows<=numberOfRows || cols<=numberOfColumns)
			return *this;
		rows = numberOfRows;
		cols = numberOfColumns;
		return *this;
	}
	Matrix &make_scan(FILE *const input){
		delete[] cp;
		double tempNew[1000];
		char line[100];
		char *linePointer = line;
		u16 i=1, j=0;

		fgets(line, 100, input);
		if(*line=='\n' || feof(input)){
			rows = 0;
			cols = 0;
			cp = NULL;
			return *this;
		}
		while(1){
			tempNew[j] = strtod(linePointer, &linePointer);
			if(*linePointer=='\n')
				break;
			j++;
		}
		cols = j+1;

		while(1){
			fgets(line, 100, input);
			linePointer = line;

			if(*linePointer=='\n' || feof(input))
				break;
			tempNew[i*cols] = strtod(linePointer, &linePointer);
			for(j=1; j<cols; j++){
				if(*linePointer=='\n' || feof(input)){
					rows = 0;
					cols = 0;
					cp = NULL;
					return *this;
				}
				tempNew[i*cols+j] = strtod(linePointer, &linePointer);
			}
			i++;
		}
		rows = i;
		i = rows*cols;
		cp = new double[i];
		for(j=0; j<i; j++)
			cp[j] = tempNew[j];
		return *this;
	}
	void print(FILE *const output, const char *const formatString="%10.3lf "){
		for(u16 i=0, j; i<rows; i++){
			for(j=0; j<cols; j++)
				fprintf(output, formatString, cp[i*cols+j]);
			putc('\n', output);
		}
	}

	// INITIALIZATIONS WITHOUT ALLOCATION
	Matrix &scan_dynamic(FILE *const input){
		for(u16 i=0, j; i<rows; i++){
			fflush(input);
			for(j=0; j<cols; j++)
				fscanf(input ,"%lf", cp+i*cols+j);
		}
		return *this;
	}
	Matrix &scan_static(FILE *const input){
		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++){
				fscanf(input ,"%lf", cp+i*cols+j);
				if(feof(input)){
					return *this;
				}
			}
		return *this;
	}
	Matrix &init_unit(){
		for(u16 i=0, j;i<rows; i++)
			for(j=0; j<cols; j++){
				if(i==j)
					cp[i*cols+j] = 1.0;
				else
					cp[i*cols+j] = 0.0;
			}
		return *this;
	}
	Matrix &init_antisym(){
		const u16 length = rows<cols ? rows:cols;

		u16 i, j;
		for(i=0; i<length; i++)
			cp[i*(length+1)]=0;
		short sign=1;
		for(i=1; i<length; i++){
			sign = -sign;
			for(j=0; j<length-i; j++){
				cp[(i+j)*length+j] = sign;
				cp[j*(length+1)+i] = -sign;
			}
		}
		return *this;
	}
	Matrix &init_number(const double scalar){
		u16 totalSize = rows*cols;
		for(u16 i; i<totalSize; i++)
			cp[i] = scalar;
		return *this;
	}
	Matrix &init_rand(const double range, const int seed){
		u16 i;
		const u16 totalSize = rows*cols;
		srand(seed);
		if(range<=0)
			for(i=0; i<totalSize; i++)
				cp[i] = 2*range*(double)(rand()-RAND_MAX/2)/(double)(RAND_MAX);
		else
			for(i=0; i<totalSize; i++)
				cp[i] = range*((double)rand()/(double)RAND_MAX);
		return *this;
	}
	Matrix &init_randint(const int range, const int seed){
		u16 i;
		const u16 totalSize = rows*cols;
		srand(seed);
		if(range==0)
			for(i=0; i<totalSize; i++)
				cp[i]=0.0;
		else if(range<0)
			for(i=0; i<totalSize; i++)
				cp[i]=(double)((rand()-RAND_MAX/2)%(1-range));
		else
			for(i=0; i<totalSize; i++)
				cp[i]=(double)(rand()%(1+range));
		return *this;
	}
	Matrix &init_papierz(){
		for(u16 i=0, j; i<rows; i++){
			for(j=0; j<i; j++)
				cp[i*cols+j]=0;
			if(j<cols)
				cp[i*cols+j++]=2;
			if(j<cols)
				cp[i*cols+j++]=1;
			if(j<cols)
				cp[i*cols+j++]=3;
			if(j<cols)
				cp[i*cols+j++]=7;
			for(; j<cols; j++)
				cp[i*cols+j]=0;
		}
		return *this;
	}	

	// OPERATIONS OF SELF
	Matrix &square(){
		if(rows!=cols)
			return *this;
		
		u16 i, j, k;
		i = cols*cols;
		double tempArray[i];
		for(j=0; j<i; j++)
			tempArray[i] = cp[i];

		double sum;		
		for(i=0; i<cols; i++)
			for(j=0; j<cols; j++){
				sum = 0.0;
				for(k=0; k<cols; k++)
					sum += tempArray[j*cols+k]*tempArray[k*cols+i];
				cp[j*cols+i] = sum;
			}	
		return *this;
	}
	Matrix &mul(const Matrix &A){
		if(rows!=A.rows || cols!=A.cols)
			return *this;
		
		if(cp=A.cp)
			return this->square();

		u16 i, j, k;
		i = cols*A.rows;
		double tempArray[i];
		for(j=0; j<i; j++)
			tempArray[i] = cp[i];

		double sum;		
		for(i=0; i<A.cols; i++)
			for(j=0; j<rows; j++){
				sum = 0.0;
				for(k=0; k<cols; k++)
					sum += tempArray[j*cols+k]*A.cp[k*A.cols+i];
				cp[j*cols+i] = sum;
			}	
		return *this;
	}
	Matrix &transpose(){
		if(rows!=cols)
			return *this;

		double temp;
		for(u16 i=0, j; i<cols; i++)
			for(j=i+1; j<cols; j++){
				temp = cp[i*cols+j];
				cp[i*cols+j] = cp[j*cols+i];
				cp[j*cols+i] = temp;
			}
		return *this;
	}
	Matrix &cofactors(){
		if(rows!=cols)
			return *this;

		u16 i, j;
		i = cols*cols;
		double tempArray[i];
		for(j=0; j<i; j++)
			tempArray[j] = cp[j];
		Matrix tempA = {cols, cols, tempArray};
		double subMatrixArray[(cols-1)*(cols-1)];
		Matrix subMatrix = {(u16)(cols-1), (u16)(cols-1), subMatrixArray};

		for(i=0; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] = ((i+j)%2?-1:1)*subMatrix.submatrix(tempA, i, j).determinant();
		return *this;
	}
	Matrix &minors(){
		if(rows!=cols)
			return *this;

		u16 i, j;
		i = cols*cols;
		double tempArray[i];
		for(j=0; j<i; j++)
			tempArray[j] = cp[j];
		Matrix tempA = {cols, cols, tempArray};
		double subMatrixArray[(cols-1)*(cols-1)];
		Matrix subMatrix = {(u16)(cols-1), (u16)(cols-1), subMatrixArray};

		for(i=0; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] = subMatrix.submatrix(tempA, i, j).determinant();
		return *this;
	}
	Matrix &inverse(){
		if(rows!=cols)
			return *this;

		double invDet = this->determinant();
		if(invDet*invDet<0.001){
			this->init_number(0.0);
			return *this;
		}

		invDet = 1/invDet;
		return this->cofactors().transpose() *= invDet;
	}

	// OPERATORS WITHOUT REALLOCATION
	Matrix &operator +=(const Matrix &A){
		if(rows>A.rows || cols>A.cols)
			return *this;

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] += A.cp[i*A.cols+j];
		return *this;
	}
	Matrix &operator -=(const Matrix &A){
		if(rows>A.rows || cols>A.cols)
			return *this;

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] -= A.cp[i*A.cols+j];
		return *this;
	}
	Matrix &operator *=(const Matrix &A){
		if(rows!=A.rows || cols!=A.cols)
			return *this;
		
		if(cp=A.cp)
			return this->square();

		u16 i, j, k;
		i = cols*A.rows;
		double tempArray[i];
		for(j=0; j<i; j++)
			tempArray[i] = cp[i];

		double sum;		
		for(i=0; i<cols; i++)
			for(j=0; j<A.rows; j++){
				sum = 0.0;
				for(k=0; k<rows; k++)
					sum += A.cp[j*cols+k]*tempArray[k*cols+i];
				cp[j*cols+i] = sum;
			}	
		return *this;
	}
	Matrix &operator *=(const double scalar){
		u16 totalSize = rows*cols;
		for(u16 i=0; i<totalSize; i++)
			cp[i] *= scalar;
		return *this;
	}
	Matrix &operator /=(const double scalar){
		u16 totalSize = rows*cols;
		for(u16 i=0; i<totalSize; i++)
			cp[i] /= scalar;
		return *this;
	}
	
	// OPRATORS WITH REALLOCATION
	Matrix operator +(const Matrix &A){
		if(rows>A.rows || cols>A.cols)
			return {0, 0, NULL};
		Matrix M(rows, cols);

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				M.cp[i*cols+j] = cp[i*cols+j]+A.cp[i*A.cols+j];
		return M;
	}
	Matrix operator -(const Matrix &A){
		if(rows>A.rows || cols>A.cols)
			return {0, 0, NULL};
		Matrix M(rows, cols);

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				M.cp[i*cols+j] = cp[i*cols+j]-A.cp[i*A.cols+j];
		return M;
	}
	Matrix operator *(const Matrix &A){
		if(cols!=A.rows)
			return {0, 0, NULL};
		Matrix M(rows, A.cols);

		double sum;
		for(u16 i=0, j, k; i<A.cols; i++)
			for(j=0; j<rows; j++){
				sum=0;
				for(k=0; k<cols; k++)
					sum += cp[j*cols+k]*A.cp[k*A.cols+i];
				M.cp[j*A.cols+i] = sum;
			}
		return M;
	}
	Matrix operator *(const double scalar){
		Matrix M(*this);
		M *= scalar;
		return M;
	}
	Matrix operator /(const double scalar){
		Matrix M(*this);
		M /= scalar;
		return M;
	}

	// OPERATIONS WITHOUT REALLOACTION
	double determinant(){
		if(rows!=cols)
			return 0;

		u16 i, j=cols*cols;
		short k;
		double cpTemp[j];
		double det=1, temp;
		for(i=0; i<j; i++)
			cpTemp[i] = cp[i];

		for(i=0; i<cols-1; i++){
			if(cpTemp[i*(cols+1)]!=0)
				goto NON_ZERO;
			for(j=cols-1; j>i; j--){
				if(cpTemp[j*cols+i]!=0){
					for(k=cols-1; k>=i; k--){
						temp = cpTemp[i*cols+k];
						cpTemp[i*cols+k] = cpTemp[j*cols+k];
						cpTemp[j*cols+k] = temp;
					}
					det = -det;
					goto NON_ZERO;
				}
			}
			return 0;
		NON_ZERO:
			det = det*cpTemp[i*(cols+1)];
			for(j=cols-1; j>i; j--){
				temp = cpTemp[j*cols+i]/cpTemp[i*(cols+1)];
				for(k=cols-1; k>i; k--)
					cpTemp[j*cols+k] = cpTemp[j*cols+k]-temp*cpTemp[i*cols+k];
			}
		}
		return det*cpTemp[cols*cols-1];
	}
	double trace(){
		u16 length = rows>cols ? rows:cols;
		double trace=0;
		for(u16 i=0; i<length; i++)
			trace = trace+cp[i*(cols+1)];
		return trace; 
	}
	Matrix &add(const Matrix &A, const Matrix &B){
		const u16 minRows = A.rows<B.rows ? A.rows : B.rows;
		const u16 minCols = A.cols<B.cols ? A.cols : B.cols;
		if(rows>minRows || cols>minCols)
			return *this;

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] = A.cp[i*A.cols+j]+B.cp[i*B.cols+j];
		return *this;
	}
	Matrix &sub(const Matrix &A, const Matrix &B){
		const u16 minRows = A.rows<B.rows ? A.rows : B.rows;
		const u16 minCols = A.cols<B.cols ? A.cols : B.cols;
		if(rows>minRows || cols>minCols)
			return *this;

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] = A.cp[i*A.cols+j]-B.cp[i*B.cols+j];
		return *this;
	}
	Matrix &mul(const Matrix &A, const Matrix &B){
		if(A.cols>B.rows || rows>A.rows || cols>B.cols)
			return *this;
		u16 i, j, k;
		
		if(cp==A.cp)
			return this->mul(B);
		if(cp==B.cp)
			return (*this *= A);

		double sum;
		for(i=0; i<B.cols; i++)
			for(j=0; j<A.rows; j++){
				sum=0;
				for(k=0; k<A.cols; k++)
					sum += A.cp[j*A.cols+k]*B.cp[k*B.cols+i];
				cp[j*cols+i] = sum;
			}
		return *this;
	}
	Matrix &submatrix(const Matrix &A, const u16 row, const u16 column){
		if(rows!=A.rows-1 || cols!=A.cols-1)
			return *this;

		for(u16 i=0, j=0, k, l; i<rows; i++, j++){
			if(j==row)
				j++;
			for(k=0, l=0; k<cols; k++, l++){
				if(l==column)
					l++;
				cp[i*cols+k] = A.cp[j*A.cols+l];
			}
		}
		return *this;
	}
	Matrix &transpose(const Matrix &A){
	if(rows!=A.cols || cols!=A.rows)
		return *this;

	if(cp==A.cp)
		return this->transpose();

	for(u16 i=0, j; i<rows; i++)
		for(j=0; j<cols; j++)
			cp[i*cols+j] = A.cp[j*rows+i];
	return *this;
}
	Matrix &cofactors(const Matrix &A){
		if(rows!=cols || rows!=A.rows || cols!=A.cols)
			return *this;

		if(cp==A.cp)
			return this->cofactors();

		double subMatrixArray[(cols-1)*(cols-1)];
		Matrix subMatrix = {(u16)(cols-1), (u16)(cols-1), subMatrixArray};

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] = ((i+j)%2?-1:1)*subMatrix.submatrix(A, i, j).determinant();
		return *this;
	}
	Matrix &minors(const Matrix &A){
		if(rows!=cols || rows!=A.rows || cols!=A.cols)
			return *this;

		if(cp==A.cp)
			return this->minors();

		double subMatrixArray[(cols-1)*(cols-1)];
		Matrix subMatrix = {(u16)(cols-1), (u16)(cols-1), subMatrixArray};

		for(u16 i=0, j; i<rows; i++)
			for(j=0; j<cols; j++)
				cp[i*cols+j] = subMatrix.submatrix(A, i, j).determinant();
		return *this;
	}
	Matrix &inverse(Matrix &A){
		if(rows!=cols || rows!=A.rows || cols!=A.cols)
			return *this;

		double invDet = A.determinant();
		if(invDet*invDet<0.001){
			this->init_number(0.0);
			return *this;
		}

		invDet = 1/invDet;
		return this->cofactors(A).transpose() *= invDet;
	}

	// OPERATIONS WITH REALLOACTION
	Matrix make_submatrix(const u16 row, const u16 column){
		Matrix M(rows-1, cols-1);
		return M.submatrix(*this, row, column);
	}
	Matrix make_transpose(){
		Matrix M(cols, rows);

		for(u16 i=0, j; i<cols; i++)
			for(j=0; j<rows; j++)
				M.cp[i*rows+j] = cp[j*cols+i];
		return M;
	}
	Matrix make_cofactors(){
		if(rows!=cols)
			return {0, 0, NULL};
		Matrix M(cols, cols);

		double subMatrixArray[(cols-1)*(cols-1)];
		Matrix subMatrix = {(u16)(cols-1), (u16)(cols-1), subMatrixArray};

		for(u16 i=0, j; i<cols; i++)
			for(j=0; j<cols; j++)
				M.cp[i*cols+j] = ((i+j)%2?-1:1)*subMatrix.submatrix(*this, i, j).determinant();
		return M;
	}
	Matrix make_minors(){
		if(rows!=cols)
			return {0, 0, NULL};
		Matrix M(cols, cols);

		double subMatrixArray[(cols-1)*(cols-1)];
		Matrix subMatrix = {(u16)(cols-1), (u16)(cols-1), subMatrixArray};

		for(u16 i=0, j; i<cols; i++)
			for(j=0; j<cols; j++)
				M.cp[i*cols+j] = subMatrix.submatrix(*this, i, j).determinant();
		return M;
	}
	Matrix make_inverse(){
		if(rows!=cols)
			return {0, 0, NULL};
		Matrix M(cols, cols);

		double invDet = this->determinant();
		if(invDet*invDet<0.001){
			M.init_number(0.0);
			return M;
		}

		invDet = 1/invDet;
		return M.cofactors(*this).transpose() *= invDet;
	}
};


int main(){
	Matrix macierz(2, 2);
	macierz.init_randint(10, time(0));
	macierz.print(stdout);

	printf("\nDet: %lf\n\n", macierz.determinant());
	putchar('\n');
	macierz.inverse().print(stdout);

	putchar('\n');
	macierz(1,1) = 21.37;
	macierz.print(stdout);

	fflush(stdin);
	getchar();
	return 0;
}