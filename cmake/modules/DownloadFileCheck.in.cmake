function(obtain_file url local_file hash_sha256)
  
  unset(local_sha256)
  set(local_sha256 "no_file")
  if(EXISTS ${local_file})
    file(SHA256 ${local_file} local_sha256)
  endif(EXISTS ${local_file})
  
  if(NOT ( ${local_sha256} STREQUAL ${hash_sha256} ) ) 
    message(STATUS "Downloading file from internet...")
    file(DOWNLOAD ${url} ${local_file} SHOW_PROGRESS)
    message(STATUS "Downloading finished")
  endif(NOT ( ${local_sha256} STREQUAL ${hash_sha256} ) ) 
  
  file(SHA256 ${local_file} local_sha256)
  
  if(NOT ( ${local_sha256} STREQUAL ${hash_sha256} ) ) 
    message(SEND_ERROR "Hash is not equal. Version changed?")
  endif(NOT ( ${local_sha256} STREQUAL ${hash_sha256} ) ) 
  
endfunction(obtain_file)