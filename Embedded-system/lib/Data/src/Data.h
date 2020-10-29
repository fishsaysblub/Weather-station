#pragma once

#define GET_ATTRIBUTE_NAME(Variable) (#Variable)
#define MAX_POST_SIZE 256

//! Post data container
/*!
    Struct containing the values to post,
    Has a method to convert data into a JSON post request.
*/
struct Data
{
    private:
        //! Formatting string
        /*!
            Formatting string to convert data into JSON like post
            A const pointer to a constexpr
        */
        static constexpr const char *post_data = "{\"%s\":%.2f, \"%s\":%.2f}";
    
    public:    
        float Temperature;
        float Humidity;

        //! Get JSON like HTTP POST data.
        /*!
            Fills a supplied char buffer with a JSON like POST
            \param buffer The buffer which will be filled with the formatted string
        */
        void GetPost(char *buffer)
        {
            sprintf(buffer, post_data, 
                GET_ATTRIBUTE_NAME(Temperature), Temperature, 
                GET_ATTRIBUTE_NAME(Humidity), Humidity);

        }
};