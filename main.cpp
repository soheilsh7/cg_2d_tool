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
        if (s[i] != ' ')
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



void add_point(vertex v, vector<edge *> es, vector<vertex *> vs)
{
    float m;
    for (int i = 0; i < edge_n; i++)
    {
        m = ((es[i]->end_vertex->x - es[i]->start_vertex->x) / (es[i]->end_vertex->y - es[i]->start_vertex->y));
        //Check Line eduation
        if (v.y == m * v.x)
        {
            if ((es[i]->start_vertex->y < v.y < es[i]->start_vertex->y) & (es[i]->start_vertex->x < v.x < es[i]->start_vertex->x))
            {
                vs.push_back(&v);
                edge e_ac(&v, es[i]->end_vertex);
                es[i]->end_vertex = &v;
                es.push_back(&e_ac);
            }
            
        }
        
    }
    
}





//TODO : set key in add_*_vector


int main(int argc, char** argv)
{
    if (argc == 1)
    {
        cout << "Enter gid file path!" << endl;
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
