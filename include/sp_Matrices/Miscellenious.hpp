namespace sp{ // BEGINING OF NAMESPACE //////////////////////////////////////////////////////////////////

template<class Prot>
Vector<Prot, uint32_t> &transposePermuts(Vector<Prot, uint32_t> *permuts);



template<class Prot>
Vector<Prot, uint32_t> &transposePermuts(Vector<Prot, uint32_t> *permuts){
	MatrixTempStorage->resize(permuts->size());
	memcpy(MatrixTempStorage->data(), permuts->data, permuts->size()*sizeof(uint32_t));
	for (uint32_t i=0; i<permuts->size(); ++i){
		(*permuts)[MatrixTempStorage->at<uint32_t>(i)] = i;
	}
	return *permuts;
}

}	// END OF NAMESPACE	///////////////////////////////////////////////////////////////////