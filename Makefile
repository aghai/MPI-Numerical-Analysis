ALL: hellow_mpi bcast_mpi jacobi_mpi ring hello_world
DIRS = struct pack

#Example 1:
#######################################################
hellow_mpi: hellow_mpi.c
	mpicc -o hellow_mpi hellow_mpi.c

#######################################################

#Example 2
########################################################
bcast_mpi: bcast_mpi.c
	mpicc -o bcast_mpi bcast_mpi.c
########################################################

#Example 3
########################################################
jacobi_mpi: jacobi_mpi.c
	mpicc -o jacobi_mpi jacobi_mpi.c -lm
########################################################
profile.alog: jacobi.c
	mpicc -o jacobi_mpi.log -mpilog jacobi_mpi.c -lm
	mpirun -np 4 jacobi_mpi.log
	/bin/mv jacobi_mpi.log_profile.log profile.alog

	#######################################################
ring: ring.c
  mpicc -o ring ring.c
  #################################################3

hello_world: hello_world
  mpicc -o hello_world hello_world.c

	#for dir in $(DIRS) ; do
	#    ( cd $$dir ; make clean ) ; done


clean:
	/bin/rm -f hellow_mpi *.o
	/bin/rm -f bcast_mpi *.o
	/bin/rm -f ring *.o
	for dir in $(DIRS) ; do
		( cd $$dir ; make clean) ; done
	/bin/rm -f jacobi_mpi jacobi_mpi.o jacobi_mpi.log
