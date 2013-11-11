#include <omni/tests/test_file_manager.hpp>
 
/**
Removes all files that have been returned by getTestFileName.
**/
omni::tests::test_file_manager::~test_file_manager ()
{
    for (auto f : _files) {
        if (boost::filesystem::exists (f)) {        
            boost::filesystem::remove (f);
        }
    }
}

/**
Creates a new path for the file with the name `fileName' in the tests directory.
If such a file exists, it is removed before the path is returned.
Files returned by this function will be removed when this test_file_manager object is destroyed.
**/
boost::filesystem::path omni::tests::test_file_manager::getTestFileName (std::string const & fileName)
{
    boost::filesystem::path path = boost::filesystem::current_path ().parent_path ();
    path /= boost::filesystem::path ("tests") /= fileName;
    _files.push_back (path);
    return path;
}
