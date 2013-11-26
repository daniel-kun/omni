#ifndef OMNI_TESTS_TEST_FILE_MANAGER_HPP
#define OMNI_TESTS_TEST_FILE_MANAGER_HPP

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace omni {
namespace tests {
    
    /**
    The test_file_manager keeps track of files created during test sessions and removes them after
    the test has finished.
    **/
    class test_file_manager {
    public:
        ~ test_file_manager ();                           

        boost::filesystem::path getTestFileName (std::string const & fileName, bool autoDelete = true);

    private:
        std::vector <boost::filesystem::path> _files;
    };

} // namespace tests
} // namespace omni

#endif
