! { dg-do run }
! Test whether use_device_ptr properly handles OPTIONAL arguments
! (Only case of present arguments is tested)
program test_it
  implicit none
  integer, target :: ixx
  integer, pointer :: ptr_i, ptr_null

  ptr_i => ixx
  call foo(ptr_i)

  ptr_null => null()
  call bar(ptr_null)
contains
  subroutine foo(ii)
    integer, pointer, optional :: ii

    if (.not.present(ii)) stop 1
    if (.not.associated(ii, ixx)) stop 2
    !$omp target data map(to:ixx) use_device_ptr(ii)
    if (.not.present(ii)) stop 3
    if (.not.associated(ii)) stop 4
    !$omp end target data
  end subroutine foo

  ! For bar, it is assumed that a NULL ptr on the host maps to NULL on the device
  subroutine bar(jj)
    integer, pointer, optional :: jj

    if (.not.present(jj)) stop 5
    if (associated(jj)) stop 6
    !$omp target data map(to:ixx) use_device_ptr(jj)
    if (.not.present(jj)) stop 7
   if (associated(jj)) stop 8
    !$omp end target data
  end subroutine bar
end program test_it
