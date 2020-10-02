#pragma once

#define GET_ATTRIBUTE_NAME(Variable) (#Variable)
#define MAX_POST_SIZE 256


struct Data
{
    private:
        // Be constant goddarnit, a const pointer to a constexpr
        static constexpr const char *post_data = "{\"%s\":%.2f, \"%s\":%.2f}";
    
    public:    
        float Temperature;
        float Humidity;

        void GetPost(char *buffer)
        {
            sprintf(buffer, post_data, 
                GET_ATTRIBUTE_NAME(Temperature), Temperature, 
                GET_ATTRIBUTE_NAME(Humidity), Humidity);

        }
};