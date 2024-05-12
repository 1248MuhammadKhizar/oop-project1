#include<iostream>
#include<sstream>
#include<string>
#include<windows.h>
#include<fstream>
#include<conio.h>
using namespace std;

class Post;
class Page;
class User;

class Post
{
private:
    int num_of_posts;
    int likes[12];
    string* post_id;
    string* date;
    string* owner;
    string* reaction;
    string* Memory;
    int* Mid;
    string like[12][12];
    string* activity;
    int* activity_id;

public:
    Post();
    ~Post();
    void readdata_from_post();
    void Display_post_data();
    void view_memory(const User&);
    void view_liked_people(const string&, const User&, const Page&);
    void like_a_Post(User&, const string&);
    string* GetCreator() const
    {
        return owner;
    }
    string getreaction(int a) const
    {
        return reaction[a];
    }
    int GetTotalPost() const
    {
        return num_of_posts;
    }

    string get_date(int a)const
    {
        return date[a];
    }
    string* get_post_id()const
    {
        return post_id;
    }


};


class Page
{

private:
    string* page_id;
    string* page_name;
    int limit;
    int size;


public:
    void change();
    Page();
    ~Page();
    void readdata_from_page(const string&);
    string get_page_name(const string&) const;
    bool Ispage(const string&) const;
    void viewpage(const string&, const Post&) const;

};



class User
{

private:
    string** Users;
    string* id;
    int numOfUser;
    int column;
    string current_user;

public:
    User();
    ~User();
    void readdata_from_user();
    void setUser(const string&);
    void view_friends_Of_User() const;
    void view_liked_pages_of_user(const Page&) const;
    void view_homepage(const Post& p);

    string GetUserName(const string&) const;
    string GetCurrent() const
    {
        return current_user;
    }
    bool IsUser(const string& userId) const;

};

class Comment
{
private:
    string* users_id;
    string* posts_id;
    string* comments_id;
    string* comments;
    int total_comments;

public:
    Comment()
    {
        ifstream file("comments.txt");
        file >> total_comments;
        users_id = new string[total_comments];
        posts_id = new string[total_comments];
        comments_id = new string[total_comments];
        comments = new string[total_comments];

        for (int i = 0; i < total_comments; i++)
        {
            file >> comments_id[i];
            file >> posts_id[i];
            file >> users_id[i];
            getline(file, comments[i]);
        }

    }
    ~Comment()
    {
        delete[] users_id;
        delete[] posts_id;
        delete[] comments_id;
        delete[] comments;

    }

    void add_comments(const string&, const string&, const string&);
    void see_comments(const string&);
};
//void User::view_homepage(const Post& p)
//{
//
//    for (int i = 0; i < numOfUser; i++)
//    {
//        if (id[i] == current_user)
//        {
//
//            cout << " User Name: " << Users[i][0] << " " << Users[i][1] << endl;
//            break;
//        }
//    }
//    string* creators = p.GetCreator();
//
//    for (int j = 0; j < numOfUser; j++)
//    {
//        if (creators[j] == current_user)
//        {
//            cout << p.getreaction(j) << endl;
//            cout << p.get_date(j) << endl;
//        }
//    }
//}
void User::view_homepage(const Post& p)
{
    bool Found = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == current_user)
        {
            Found = true;
            cout << "User Name: " << Users[i][0] << " " << Users[i][1] << "\n";
            break;
        }
    }
    if (!Found)
    {
        cout << "User not found!" << endl;
        return;
    }

    string* creators = p.GetCreator();
    cout << "Current User: " << current_user << endl;
    cout << "Creators array:" << endl;
    for (int i = 0; i < p.GetTotalPost(); i++)
    {
        cout << creators[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < p.GetTotalPost(); i++)
    {
        if (creators[i] == current_user)
        {
            cout << "Post ID: " << p.get_post_id()[i] << endl; 
            cout << "Content: " << p.getreaction(i) << endl; 
            cout << "Date: " << p.get_date(i) << endl;
        }
    }
}


Post::Post()
{
    readdata_from_post();
}

Post::~Post()
{
    delete[] post_id;
    delete[] date;
    delete[] reaction;
    delete[] owner;
}



void Post::view_memory(const User& user)
{
    string temp_user = user.GetCurrent();
    for (int i = 0; i < num_of_posts; i++)
    {
        if (owner[i] == temp_user)
        {
            if (Mid[i] == 1)
            {
                
                cout << " Feeling " << Memory[i] << endl;
                cout << reaction[i] << endl;
            }
            else if (Mid[i] == 2)
            {
                cout << " Thinking About " << Memory[i] << endl;
                cout << reaction[i] << "\n";
            }
            else if (Mid[i] == 3)
            {
                cout << " Making " << Memory[i] << endl;
                cout << reaction[i] << endl;

            }
            else if (Mid[i] == 4)
            {
                cout << " Celebrating " << Memory[i] << endl;
                cout << reaction[i] << "\n";

            }
        }
    }
}

void Post::readdata_from_post()
{
    ifstream file("post.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    file >> num_of_posts;
    post_id = new string[num_of_posts];
    date = new string[num_of_posts];
    reaction = new string[num_of_posts];
    Mid = new int[num_of_posts];
    Memory = new string[num_of_posts];
    owner = new string[num_of_posts];
    for (int i = 0; i < num_of_posts; i++)
    {
        file >> likes[i];
        file >> post_id[i];
        file >> date[i];
        file.ignore();
        getline(file, reaction[i]);
        file >> Mid[i];
        getline(file, Memory[i]);
        getline(file, owner[i]);
        int j = 0;
        while (true) {
            file >> like[i][j];
            if (like[i][j] == "-1" || like[i][j].empty()) break;
            j++;
        }
    }
    file.close();
}


void Post::view_liked_people(const string& postId, const User& users, const Page& pages)
{
    bool Found = false;
    for (int i = 0; i < num_of_posts; i++)
    {
        if (post_id[i] == postId)
        {
            Found = true;
            cout << "Post ID  " << post_id[i] << endl;
            cout << "Content  " << reaction[i] << endl;
            cout << "Creator  " << owner[i] << endl;
            cout << "Liked by " << endl;

            int j = 0;
            while (like[i][j] != "-1")
            {
                string liker = like[i][j];
                if (users.IsUser(liker))
                {
                    cout << users.GetUserName(liker);
                }
                else if (pages.Ispage(liker))
                {
                    cout << pages.get_page_name(liker);
                }
                if (like[i][j + 1] != "-1")
                {
                    cout << ", ";
                }
                j++;
            }
            cout << endl;
            break;
        }
    }
    if (!Found)
    {
        cout << "Post with ID " << postId << " not found." << endl;
    }
}


void Post::like_a_Post(User& users, const string& postId) {
    string currentUserId = users.GetCurrent();
    for (int i = 0; i < num_of_posts; i++)
    {
        if (post_id[i] == postId)
        {
            bool Liked = false;
            for (int j = 0; j < 10; j++)
            {
                if (like[i][j] == currentUserId)
                {
                    Liked = true;
                    break;
                }
            }
            if (Liked) {
                cout << " Liked already " << endl;
            }
            else if (likes[i] < 10)
            {
                int k = likes[i];
                like[i][k] = currentUserId;
                like[i][k + 1] = "-1";
                ++likes[i];
                cout << " Liked the post successfully" << endl;
            }
            else
            {
                cout << "Maximum number of likes reached for this post." << endl;
            }
            break;
        }
    }
}

void Post::Display_post_data() {
    for (int i = 0; i < num_of_posts; i++) {
        cout << "Likes " << likes[i] << endl;
        cout << "Post ID " << post_id[i] << endl;
        cout << "Date " << date[i] << endl;
        cout << "Content " << reaction[i] << endl;
        cout << "Created By: " << owner[i] << endl;
        cout << "Liked by ";
        for (int j = 0; like[i][j] != "-1"; j++)
        {
            cout << like[i][j] << " ";
        }
        cout << endl;
    }
}

//function of Page

Page::Page() : limit(10), size(0)
{
    page_id = new string[limit];
    page_name = new string[limit];
}

Page::~Page()
{
    delete[] page_id;
    delete[] page_name;
}

void Page::readdata_from_page(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error file not opened " << filename << endl;
        return;
    }

    string a;
    while (getline(file, a))
    {
        stringstream ss(a);
        string temp_id, temp_name;
        ss >> temp_id;
        getline(ss, temp_name);

        if (size == limit)
        {
            change();
        }
        page_id[size] = temp_id;
        page_name[size] = temp_name;
        size++;
    }

    file.close();
}



bool Page::Ispage(const string& pg___id) const
{
    for (int i = 0; i < size; i++)
    {
        if (page_id[i] == pg___id)
        {
            return true;
        }
    }
    return false;
}

string Page::get_page_name(const string& pageId) const
{
    for (int i = 0; i < size; i++)
    {
        if (page_id[i] == pageId)
        {
            return page_name[i];
        }
    }
    return "false";
}


void Page::viewpage(const string& userId, const Post& p) const
{
    string* creators = p.GetCreator();
    for (int i = 0; i < p.GetTotalPost(); i++)
    {
        if (creators[i] == userId)
        {
            cout << "Content " << p.getreaction(i) << endl;
        }
    }
}


void Page::change() {
    limit *= 2;
    string* a = new string[limit];
    string* b = new string[limit];
    for (size_t i = 0; i < size; i++) {
        a[i] = page_id[i];
        b[i] = page_name[i];
    }

    delete[] page_id;
    delete[] page_name;
    page_id = a;
    page_name = b;
    size++;
}



// declaration of user functions

User::User() {
    readdata_from_user();
}

User::~User() {
    delete[] id;
    for (int i = 0; i < numOfUser; i++) {
        delete[] Users[i];
    }
    delete[] Users;
}

void User::readdata_from_user() {
    ifstream file("user.txt");
    if (!file.is_open()) {
        cout << "Error in opening File \n";
    }
    string line;
    getline(file, line);
    stringstream header(line);
    column = 0;
    string a;
    while (header >> a) {
        column++;
    }

    numOfUser = 0;
    while (getline(file, line))
    {
        numOfUser++;
    }
    file.clear();
    file.seekg(0, ios::beg);
    id = new string[numOfUser];
    Users = new string * [numOfUser];
    for (int i = 0; i < numOfUser; i++)
    {
        Users[i] = new string[column];
    }
    int Index = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string user_idss;
        ss >> user_idss;
        if (Index < numOfUser)
        {
            id[Index] = user_idss;
            for (int i = 0; i < column; i++)
            {
                ss >> Users[Index][i];
            }
            Index++;
        }
    }
    file.close();
}

string User::GetUserName(const string& userId) const
{
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == userId)
        {
            return Users[i][0] + " " + Users[i][1];
        }
    }
    return "User not found";
}

void User::setUser(const string& a)
{
    bool user_found = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == a) {
            current_user = a;
            user_found = true;
            cout << "Current User: " << current_user << endl;
            cout << Users[i][0] << " " << Users[i][1] << " is set as current user" << endl;
            break;
        }
    }
    if (!user_found)
    {
        cout << "User not found  " << a << endl;
    }
}

bool User::IsUser(const string& Id) const
{
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == Id)
        {
            return true;
        }
    }
    return false;
}

void User::view_liked_pages_of_user(const Page& pages) const
{
    bool currentUserFound = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == current_user)
        {
            currentUserFound = true;
            cout << Users[i][0] << " " << Users[i][1] << " " << " liked pages " << endl;
            for (int j = 2; j < column; j++)
            {
                string likedPageId = Users[i][j];
                if (pages.Ispage(likedPageId))
                {
                    string pageName = pages.get_page_name(likedPageId);

                    cout << likedPageId << " " << pageName << endl;

                }
            }
            break;
        }
    }
    if (!currentUserFound)
    {
        cout << "Current user " << current_user << " not found. Please set a valid current user." << endl;
    }
}


void User::view_friends_Of_User() const
{
    bool found = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == current_user)
        {
            found = true;
            cout << "Friends of " << Users[i][0] << " " << Users[i][1] << " " << current_user << endl;
            for (int j = 2; j < column; j++)
            {
                string friend_id = Users[i][j];
                for (int k = 0; k < numOfUser; k++)
                {
                    if (id[k] == friend_id) {
                        cout << Users[k][0] << " " << Users[k][1] << " " << friend_id << endl;
                        break;
                    }
                }
            }
            return;
        }
    }
    if (!found) {
        cout << "user not set" << endl;
    }
}

void Comment::add_comments(const string& user, const string& post, const string& comment)
{
    // addition of one comment
    string* temp_comment = new string[total_comments + 1];
    string* temp_user_id = new string[total_comments + 1];
    string* temp_comment_id = new string[total_comments + 1];
    string* temp_post_id = new string[total_comments + 1];

    //copy  comments
    for (int i = 0; i < total_comments; i++)
    {
        temp_comment_id[i] = comments_id[i];
        temp_comment[i] = comments[i];
        temp_user_id[i] = users_id[i];
        temp_post_id[i] = posts_id[i];

    }

    temp_comment[total_comments] = comment;
    temp_user_id[total_comments] = user;
    temp_post_id[total_comments] = post;
    string temp = "C" + to_string(total_comments);
    temp_comment_id[total_comments] = temp;
    delete[] comments_id;
    delete[] users_id;
    delete[] posts_id;
    delete[] comments;


    comments_id = temp_comment_id;
    posts_id = temp_post_id;
    users_id = temp_user_id;
    comments = temp_comment;
    total_comments += 1;

}

void Comment::see_comments(const string& c)
{
    bool found = false;
    for (int i = 0; i < total_comments; i++)
    {
        if (c == posts_id[i])
        {
            found = true;
            cout << comments_id[i] << " " << users_id[i] << "   " << posts_id[i] << "  " << comments[i] << endl;
        }

    }
    if (found == false)
    {
        cout << " No comments Yet " << endl;
    }

}



void run_application()
{
User u1;
    Page p;
    Post p1;
    Comment c1;    
    p.readdata_from_page("page.txt");
   
    string user;
    cout << "Enter User ID: ";
    cin >> user;

    bool found = false;
    do 
    {
        if (u1.IsUser(user)) 
        {
            found = true;
            u1.setUser(user);
        }
        else
        {
            cout << "User not found. Enter User ID: ";
            cin >> user;
        }
    } while (!found);

    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"PLEASE WAIT WHILE WE SET UP YOUR ACCOUNT AND CHECK YOUR ACCOUNT SECURITY"<<endl;
    Sleep(3000);
    cout<<"-------------------------------------------------------------------------------"<<endl;
    cout<<"IMFORMATION VERIFIED_________ Press any key to continue"<<endl;
    _getch();

    
    

    int choice;
    do 
    {
        cout    << "Press the following keys to perform "<<endl;
        cout    << "1. view friends of User\n";
        cout    << "2. View Liked People of a Post\n";
        cout    << "3. Like a Post\n";
        cout    << "4. Set User\n";
        cout    << "5. View Liked Pages\n";
        cout    << "6.View Page\n";
        cout    << "7.See Home Page\n";
        cout    <<"8. See Memory\n";
        cout    <<"9. View Comment on Post \n";
        cout    <<"10. Add Comment \n";
        cout    << "0. Exit\n";
        cout    << "Enter your choice: "<<endl;
        cin >> choice;
        if(choice==1) {
        
            u1.view_friends_Of_User();
        }
        else if(choice==2) {
            string postId;
            cout << "Enter Post ID: ";
            cin >> postId;
            p1.view_liked_people(postId, u1, p);
    
        }
        
        else if(choice==3) {
            string postId;
            cout << "Enter Post ID: ";
            cin >> postId;
            p1.like_a_Post(u1, postId);
            
        }

        else if(choice==4) {
            cout << "Enter User ID: ";
            cin >> user;
            if (u1.IsUser(user)) 
            {
                u1.setUser(user);
            }
            else
            {
                cout << "User not found.\n";
            }
        
        }
        else if(choice==5) 
        {
            u1.view_liked_pages_of_user(p);
        
        }
        else if(choice==6)
        {
            string Page;
            cout<<"Enter Page : ";
            cin >> Page;
            p.viewpage(Page, p1);

        }
        
        else if(choice==7)
        {
            u1.view_homepage(p1);
        
        }
       else if(choice==8)
        {
            p1.view_memory(u1);
        
        }
       else if(choice==9)
        {
            string post;
            cout << " Enter Post ID :";
            cin >> post;
             
            c1.see_comments(post);
        
        }

       else if(choice==10) 
        {
            string post;
            cout << " Enter Post : ";
            cin >> post;
            cin.ignore(); 
            string Comm;
            cout << " Enter Comment :";
            getline(cin, Comm);
            c1.add_comments(u1.GetCurrent(), post, Comm);
        
        }

        else if(choice==0)
        {
            break;
        }
        
        else{
            cout << "Invalid option! Please try again.\n";
        }


        cout<<" Press any key to further run the program "<<endl;
        _getch();
        Sleep(1000);
    } while (choice != 0);
}




int main()
{
    run_application();
}

