#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>

using namespace std;

#include "dcel.hpp"
#include "show.hpp"

/*
void SetLineEnding(char *filename, std::string &newline, string &delimiter)
{
    std::string str;
    std::ifstream chk(filename,std::ios::binary);
    if(getline(chk, str))
    {
        if(str.size() && str[str.size()-1] == '\r') 
        {
            //It can be either \r or \r\n
            if(getline(chk, str))
            {
                delimiter = '\n';
                newline = "\\r\\n";
            }
            else
            {
                delimiter = '\r';
                newline = "\\r";
            }
        }
        else 
        {
            delimiter = '\n';
            newline = "\\n";
        }
    }
}

*/

int filter(string s, vector<string> *elements)
{

    //BUG : First element is ' ' :/
    int indicator = 0;
    string element;
    bool in_flag = false, added = false;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != ' ' && s[i] != '\t')
        {
            added = false;
            in_flag =true;
            element += s[i];
            
        }
        else
        {
            in_flag = false;
        }
        
        if (!in_flag && !added)
        {
            added = true;
            elements->push_back(element);
            indicator ++;
            element.clear();
        }
    }
    elements->push_back(element);
    indicator ++;
    return indicator;
    
}

float distance(vertex v1, vertex v2)
{
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

vertex midpoint_2(vertex v1, vertex v2)
{
    vertex v;
    v.x = (v1.x + v2.x) / 2;
    v.y = (v1.y + v2.y) / 2;
    return v;
}

vertex midpoint_3(vertex v1, vertex v2, vertex v3)
{
    vertex v;
    v.x = (v1.x + v2.x + v3.x) / 3;
    v.y = (v1.y + v2.y + v3.y) / 3;
    return v;
}

std::string extractLastNChars(std::string const &str, int n)
{
    if (str.size() < n) {
        return str;
    }
 
    return str.substr(str.size() - n);
}

//TODO : set key in add_*_vector

bool read_file(string file_name, vector<vertex>& points, vector<edge>& edges, vector<face>& faces)
{
    cout << "Reading file " << file_name << endl;
    int vec_num;
    vector<string> elements;

    if (extractLastNChars(file_name, 4) == ".gid")
    {
        cout << ".gid file" << endl;
        fstream gid_file;
        gid_file.open(file_name, ios::in);
    
        string inp;
        char del = '\r';

        //dimention of mesh
        getline(gid_file, inp, del);
        cout << inp;

        //number of points
        getline(gid_file, inp, del);
        cout << inp;
        vec_num = filter(inp, &elements);
        int number_of_points = stoi(elements[1]);
        elements.clear();


        //number of cells
        getline(gid_file, inp, del);
        cout << inp;
        vec_num = filter(inp, &elements);
        int number_of_cells = stoi(elements[1]);
        elements.clear();

        //number of faces
        getline(gid_file, inp, del);
        cout << inp;
        vec_num = filter(inp, &elements);
        int number_of_faces = stoi(elements[1]);
        elements.clear();

        //number of regions
        getline(gid_file, inp, del);
        cout << inp;


        cout << "\n=======================================" << endl;


        int i = 0;
        int point_iter = 0;
        stringstream stream;
        long double ac_x, ac_y;
        while (getline(gid_file, inp, del))
        {
            //add points
            i ++;
            if (i >= 7 + number_of_faces && i < 7 + number_of_faces + number_of_points)
            {
                filter(inp,&elements);
                //points[point_iter] = new vertex(stold(elements[1]),stoi(elements[2])) ;
                stream << elements[1];
                stream >> ac_x;
                stream.clear();
                stream << elements[2];
                stream >> ac_y;
                stream.clear();
                vertex v_ac(ac_x,ac_y); 
                points.push_back(v_ac);
                //cout << "\np" << v_ac.get_key() << " = " << v_ac.x << "\t" << v_ac.y;
                elements.clear();
            }
            //cout << points[1].get_key() << " = " << points[1].x << "\t" << points[1].y << endl;

        }
        //cout << points[11976].get_key() << " = " << points[11976].x << "\t" << points[11976].y << endl;
        gid_file.clear();
        gid_file.seekg(0);

        //create face pointers
        for (int j = 0; j <= number_of_cells; j++)
        {
            face f_ac;
            faces.push_back(f_ac);
        }


        //add edges + faces
        i = 0;
        int n=0;
        int index_key = 0;
        while (getline(gid_file, inp, del))
        {
            i++;
            if (i >= 11 && i < 11 + number_of_faces)
            {
        
                filter(inp,&elements);
                edge e_ac(&points[stoi(elements[4])],&points[stoi(elements[5])]); 
                e_ac.set_key(index_key);
                index_key ++;
                edges.push_back(e_ac);
                //cout << elements[2] << "--------" <<  elements[3] << "---------" << elements[4] << "--------" <<  elements[5] << endl;
                //add edge to faces
            
                faces[stoi(elements[2])].add_edge(&edges.back()); //Left cell
                faces[stoi(elements[3])].add_edge(&edges.back()); //Right cell

                faces[stoi(elements[2])].add_edge(&edges.back()); //Left cell
                faces[stoi(elements[3])].add_edge(&edges.back()); //Right cell

                //add points to faces
                //faces[stoi(elements[2])].add_vertex(edges.back().start_vertex);
                //faces[stoi(elements[2])].add_vertex(edges.back().end_vertex);

                //faces[stoi(elements[3])].add_vertex(edges.back().start_vertex);
                //faces[stoi(elements[3])].add_vertex(edges.back().end_vertex);
            
                elements.clear();
                n++;
                //cout << "\ne" << e_ac.get_key() << " = " << e_ac.start_vertex->get_key() << "\t" << e_ac.end_vertex->get_key();
            }
            //cout << points[1].get_key() << " = " << points[1].x << "\t" << points[1].y << endl;
        }
        //gid_file.clear();
        //gid_file.seekg(0);

        faces[1].print();
        cout << faces[1].edges[0]->get_key() ;

        //show(points);

        gid_file.close();
        return true;
    }

    else if (extractLastNChars(file_name, 4) == ".plt")
    {
        cout << ".plt file" << endl;

        int number_of_points;

        fstream plt_file;
        plt_file.open(file_name, ios::in);
    
        string inp;
        char del = '\r';

        //Variables
        getline(plt_file, inp, del);
        cout << "\n" << inp << endl;

        //Zone
        getline(plt_file, inp, del);
        cout << inp << endl;
        
        filter(inp,&elements);
        number_of_points = stoi(elements[4]);
        cout << "Number of points : " << number_of_points << endl;
        elements.clear();

        cout << "\n=======================================" << endl;

        

        int i = 0;
        int point_iter = 0;
        stringstream stream;
        long double ac_x, ac_y;
        while (getline(plt_file, inp, del))
        {
            //add points
            i ++;
            if (i >= 0  && i < number_of_points)
            {
                filter(inp,&elements);
                //points[point_iter] = new vertex(stold(elements[1]),stoi(elements[2])) ;
                stream << elements[1];
                stream >> ac_x;
                stream.clear();
                stream << elements[2];
                stream >> ac_y;
                stream.clear();
                vertex v_ac(ac_x,ac_y); 
                points.push_back(v_ac);
                //cout << "\np" << v_ac.get_key() << " = " << v_ac.x << "\t" << v_ac.y;
                elements.clear();
            }
            //cout << points[1].get_key() << " = " << points[1].x << "\t" << points[1].y << endl;

        }
        //cout << points[11976].get_key() << " = " << points[11976].x << "\t" << points[11976].y << endl;
        plt_file.clear();
        plt_file.seekg(0);

        /*
        //create face pointers
        for (int j = 0; j <= number_of_cells; j++)
        {
            face f_ac;
            faces.push_back(f_ac);
        }


        //add edges + faces
        i = 0;
        int n=0;
        int index_key = 0;
        while (getline(plt_file, inp, del))
        {
            i++;
            if (i >= 11 && i < 11 + number_of_faces)
            {
        
                filter(inp,&elements);
                edge e_ac(&points[stoi(elements[4])],&points[stoi(elements[5])]); 
                e_ac.set_key(index_key);
                index_key ++;
                edges.push_back(e_ac);
                //cout << elements[2] << "--------" <<  elements[3] << "---------" << elements[4] << "--------" <<  elements[5] << endl;
                //add edge to faces
            
                faces[stoi(elements[2])].add_edge(&edges.back()); //Left cell
                faces[stoi(elements[3])].add_edge(&edges.back()); //Right cell

                faces[stoi(elements[2])].add_edge(&edges.back()); //Left cell
                faces[stoi(elements[3])].add_edge(&edges.back()); //Right cell

                //add points to faces
                //faces[stoi(elements[2])].add_vertex(edges.back().start_vertex);
                //faces[stoi(elements[2])].add_vertex(edges.back().end_vertex);

                //faces[stoi(elements[3])].add_vertex(edges.back().start_vertex);
                //faces[stoi(elements[3])].add_vertex(edges.back().end_vertex);
            
                elements.clear();
                n++;
                //cout << "\ne" << e_ac.get_key() << " = " << e_ac.start_vertex->get_key() << "\t" << e_ac.end_vertex->get_key();
            }
            //cout << points[1].get_key() << " = " << points[1].x << "\t" << points[1].y << endl;
        }

        faces[1].print();
        cout << faces[1].edges[0]->get_key() ;

        //show(points);

        */

        plt_file.close();

        return true;
    }
    

    else
    {
        cout << "File not found or is an unsupported type" << endl;
        cout << "Supported types: .gid, .plt" << endl;
        return false;
    }
    

}


int main(int argc, char** argv)
{
    if (argc == 1)
    {
        cout << "Enter file path as an argument!" << endl;
        return 1;
    }

    vector<vertex> points;
    vector<edge> edges;
    vector<face> faces;

    if (read_file(argv[1], points, edges, faces))
    {
        cout << "\nFile read successfully!" << endl;
        show(points);
    }
    else
    {
        cout << "\nFile read failed!" << endl;
    }

}



/*

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        cout << "Enter file path as an argument!" << endl;
        return 1;
    }
    

    int vec_num;
    vector<string> elements;

    vector<vertex> points;
    vector<edge> edges;
    vector<face> faces;



    fstream gid_file;
    gid_file.open(argv[1], ios::in);

    //string newLine;
 
    //string delimiter;
    //SetLineEnding(argv[1], newLine, delimiter);
    
    string inp;
    char del = '\r';

    //dimention of mesh
    getline(gid_file, inp, del);
    cout << inp;

    //number of points
    getline(gid_file, inp, del);
    cout << inp;
    vec_num = filter(inp, &elements);
    int number_of_points = stoi(elements[1]);
    elements.clear();


    //number of cells
    getline(gid_file, inp, del);
    cout << inp;
    vec_num = filter(inp, &elements);
    int number_of_cells = stoi(elements[1]);
    elements.clear();

    //number of faces
    getline(gid_file, inp, del);
    cout << inp;
    vec_num = filter(inp, &elements);
    int number_of_faces = stoi(elements[1]);
    elements.clear();

    //number of regions
    getline(gid_file, inp, del);
    cout << inp;


    cout << "\n=======================================" << endl;


    int i = 0;
    int point_iter = 0;
    stringstream stream;
    long double ac_x, ac_y;
    while (getline(gid_file, inp, del))
    {
        //add points
        i ++;
        if (i >= 7 + number_of_faces && i < 7 + number_of_faces + number_of_points)
        {
            filter(inp,&elements);
            //points[point_iter] = new vertex(stold(elements[1]),stoi(elements[2])) ;
            stream << elements[1];
            stream >> ac_x;
            stream.clear();
            stream << elements[2];
            stream >> ac_y;
            stream.clear();
            vertex v_ac(ac_x,ac_y); 
            points.push_back(v_ac);
            //cout << "\np" << v_ac.get_key() << " = " << v_ac.x << "\t" << v_ac.y;
            elements.clear();
            
        }
        //cout << points[1].get_key() << " = " << points[1].x << "\t" << points[1].y << endl;

    }
    //cout << points[11976].get_key() << " = " << points[11976].x << "\t" << points[11976].y << endl;
    gid_file.clear();
    gid_file.seekg(0);

    //create face pointers
    for (int j = 0; j <= number_of_cells; j++)
    {
        face f_ac;
        faces.push_back(f_ac);
    }
    


    //add edges + faces
    i = 0;
    int n=0;
    int index_key = 0;
    while (getline(gid_file, inp, del))
    {
        i++;
        if (i >= 11 && i < 11 + number_of_faces)
        {
        
            filter(inp,&elements);
            edge e_ac(&points[stoi(elements[4])],&points[stoi(elements[5])]); 
            e_ac.set_key(index_key);
            index_key ++;
            edges.push_back(e_ac);
            
            //cout << elements[2] << "--------" <<  elements[3] << "---------" << elements[4] << "--------" <<  elements[5] << endl;
            //add edge to faces
            
            faces[stoi(elements[2])].add_edge(&edges.back()); //Left cell
            faces[stoi(elements[3])].add_edge(&edges.back()); //Right cell

            faces[stoi(elements[2])].add_edge(&edges.back()); //Left cell
            faces[stoi(elements[3])].add_edge(&edges.back()); //Right cell

            //add points to faces
            //faces[stoi(elements[2])].add_vertex(edges.back().start_vertex);
            //faces[stoi(elements[2])].add_vertex(edges.back().end_vertex);

            //faces[stoi(elements[3])].add_vertex(edges.back().start_vertex);
            //faces[stoi(elements[3])].add_vertex(edges.back().end_vertex);
            
            elements.clear();
            n++;
            //cout << "\ne" << e_ac.get_key() << " = " << e_ac.start_vertex->get_key() << "\t" << e_ac.end_vertex->get_key();
        }
        //cout << points[1].get_key() << " = " << points[1].x << "\t" << points[1].y << endl;
    }
    //gid_file.clear();
    //gid_file.seekg(0);

    faces[1].print();
    cout << faces[1].edges[0]->get_key() ;

    show(points);

    gid_file.close();

}

*/
