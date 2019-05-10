
cdef extern from "snapshot.h": 
	int populate_data_from_file(SNAPSHOT *snap, char *file, char comment) 
	void free_snapshot(SNAPSHOT *snap)

