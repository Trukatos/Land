#include "landmassdetector.h"
#include "ui_landmassdetector.h"
#include "Landmass.h"
#include "iostream"
#include "fstream"
#include "string"
#include "list"
#include "sstream"
#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QPushButton>
#include <windows.h>

LandmassDetector::LandmassDetector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LandmassDetector)
{
    ui->setupUi(this);
}

LandmassDetector::~LandmassDetector()
{
    delete ui;
    delete landmasses;
}

using namespace std;

string border_colors [] = {"red", "blue", "yellow", "purple", "orange", "brown", "black", "white", "lightred", "lightblue", "lightgreen","pink"};
Dialog* dialog;

void LandmassDetector::merge_landmasses(int left, int mid, int right, Landmass* lm) {
    int first_val = 0, last_val = 0;

    for (list<Landmass>::iterator it = landmasses->begin(); it != landmasses->end(); it++) {
        list<int> prev_line_indices = it->get_prev_line_indices();
        if (!prev_line_indices.empty())
        {
            first_val = prev_line_indices.front();
            last_val = prev_line_indices.back();
            if (((first_val <= left) && (last_val >= left))
                | ((first_val <= mid) && (last_val >= mid))
                | ((first_val <= right) && (last_val >= right)))
            {
                if (it->prev_line_indices_contains(left, mid, right))
                {
                    lm->merge_values(*it);
                    landmasses->erase(it);
                    return;
                }

            }
        }
    }
}

void LandmassDetector::detection(string map_name, Dialog* d)
{
    const char* app_name = "LandmassDetector application developed by Mathias Assmann";
    ifstream map(map_name);
    dialog = d;
    if (map.is_open()) {
        landmasses = new list<Landmass>();
        int map_max_height_index = 49;
        int map_max_width_index = 79;
        //actual width and height decreased by one to be consistent with the array indices given by getline(map, line)
        this->setWindowTitle(app_name);
        string img_path = "./images/";
        string img_format = ".jpg";
        int x = 10, y = 20, w = 10, h = 10;
        QLabel* label;
        QPixmap* pix;
        char watersymbol = '.';
        string cur_line, prev_line, next_line = "";
        getline(map, next_line);
        bool prev_is_lm = false;
        //flag that states if the previously checked symbol/location is a landmass
        Landmass *cur_landmass;
        cur_landmass = new Landmass();
        int left_neighbor, right_neighbor;
        int line_index = 0;
        while (line_index <= map_max_height_index)
        {
            x=10;
            prev_line = cur_line;
            cur_line = next_line;
            getline(map, next_line);
            //
            if (!cur_landmass->get_cur_line_indices().empty())
            {
                cur_landmass = new Landmass();
            }
            for (int i = 0; i <= map_max_width_index; i++)
            {
                if (cur_line[i] == watersymbol)
                {
                    label = new QLabel(this);
                    label->setGeometry(x, y, w, h);
                    pix = new QPixmap((img_path + "water" + img_format).c_str());
                    label->setPixmap(*pix);
                    /*
                    This case is checked to prevent the creation of
                    a new landmass for each non-landmass-location
                    */
                    if (prev_is_lm)
                    {
                        if (!cur_landmass->get_cur_line_indices().empty())
                        {
                            cur_landmass->add_vertical_border_piece(x,y);
                            landmasses->push_back(*cur_landmass);
                            cur_landmass = new Landmass();
                        }
                        prev_is_lm = false;
                    }
                    x+=10;
                }
                else
                    //currernt location is a landmass
                {
                    char c = cur_line[i];
                    string symbol;
                    if (c == '+')
                    {
                        cur_landmass->inc_land();
                        symbol = "land";
                    }
                    else if (c == '*')
                    {
                        cur_landmass->inc_tree();
                        symbol = "tree";
                    }
                    else if (c == '^')
                    {
                        cur_landmass->inc_mountain();
                        symbol = "mountain";
                    }
                    /*checked to prevent inapproiate behaviour if the map width given by the user
                     * is greater than the actual width of the map
                     */
                    else if (c == '@')
                    {
                        cur_landmass->inc_building();
                        symbol = "building";
                    }
                    label = new QLabel(this);
                    label->setGeometry(x, y, w, h);
                    pix = new QPixmap((img_path + symbol + img_format).c_str());
                    label->setPixmap(*pix);
                    if(!prev_is_lm && i != 0)
                    {
                       cur_landmass->add_vertical_border_piece(x-3,y);
                    }
                    if(prev_line[i] == watersymbol)
                        cur_landmass->add_horizontal_border_piece(x,y-3);
                    if(next_line[i] == watersymbol)
                        cur_landmass->add_horizontal_border_piece(x,y+10);
                    x+=10;
                    cur_landmass->add_cur_line_index(i);
                    prev_is_lm = true;
                    (i - 1 < 0) ? left_neighbor = 0 : left_neighbor = i - 1;
                    (i + 1 > map_max_width_index) ? right_neighbor = i : right_neighbor = i + 1;
                    /* The following case is true for the first line where prev_line is still empty, but
                     *  the method merge_landmasses skips its for-loop because the list landmasses is still empty.
                     */
                    if ((prev_line[left_neighbor] != watersymbol)
                        | (prev_line[i] != watersymbol)
                        | (prev_line[right_neighbor] != watersymbol))
                    {
                        merge_landmasses(left_neighbor, i, right_neighbor, cur_landmass);
                    }
                }
            }
            //end of line reached
            //The following case is true if the last symbol in a given line is non-water location
            if (!cur_landmass->get_cur_line_indices().empty()) {
                landmasses->push_back(*cur_landmass);
            }
            prev_is_lm = false;
            line_index++;
            y+=10;
            for (list<Landmass>::iterator it = landmasses->begin(); it != landmasses->end(); it++)
            {
                it->update_indices();
            }
        } //end of while
        map.close();

        //OUTPUT
        x = 10, y += 20, w = 260, h = 20;
        label = new QLabel(this);        
        string output_string = to_string(landmasses->size()) + " landmasses detected in " + map_name.substr(map_name.find_last_of("/")+1) + ":";
        label->setGeometry(x,y,w,h);
        label->setText(output_string.c_str());
        label->setStyleSheet("QLabel { font-weight : bold}");
        int i = 1;
        y += 40;
        for (list<Landmass>::iterator it = landmasses->begin(); it != landmasses->end(); it++)
        {
            output_string = "Island " + to_string(i) + " - " + to_string(it->get_land() + it->get_tree()
                             + it->get_mountain() + it->get_building()) + " locations:\n";
            // border_color
            label = new QLabel(this);
            label->setGeometry(x,y+2,10,3);
            label->setStyleSheet(("QLabel { background-color : " + border_colors[i-1] + "}").c_str());
            //location sum
            label = new QLabel(this);
            label->setGeometry(x+12,y,w,h);
            label->setText(output_string.c_str());
            //land_count
            label = new QLabel(this);
            label->setGeometry(x,y+15,40,h);
            label->setAlignment(Qt::AlignRight);
            label->setText((to_string(it->get_land()) + " x ").c_str());
            //land_symbol
            label = new QLabel(this);
            label->setGeometry(x+40,y+17,10,10);
            pix = new QPixmap((img_path + "land" + img_format).c_str());
            label->setPixmap(*pix);
            //tree_count
            label = new QLabel(this);
            label->setGeometry(x+60,y+15,40,h);
            label->setAlignment(Qt::AlignRight);
            label->setText((to_string(it->get_tree()) + " x ").c_str());
            //tree_symbol
            label = new QLabel(this);
            label->setGeometry(x+100,y+17,10,10);
            pix = new QPixmap((img_path + "tree" + img_format).c_str());
            label->setPixmap(*pix);
            //mountain_count
            label = new QLabel(this);
            label->setGeometry(x,y+30,40,h);
            label->setAlignment(Qt::AlignRight);
            label->setText((to_string(it->get_mountain()) + " x ").c_str());
            //mountain_symbol
            label = new QLabel(this);
            label->setGeometry(x+40,y+32,10,10);
            pix = new QPixmap((img_path + "mountain" + img_format).c_str());
            label->setPixmap(*pix);
            //building_count
            label = new QLabel(this);
            label->setGeometry(x+60,y+30,40,h);
            label->setAlignment(Qt::AlignRight);
            label->setText((to_string(it->get_building()) + " x ").c_str());
            //tree_symbol
            label = new QLabel(this);
            label->setGeometry(x+100,y+32,10,10);
            pix = new QPixmap((img_path + "building" + img_format).c_str());
            label->setPixmap(*pix);
            if(i%3==0) {
                y+=60;
                x=10;
            } else
                x+=250;

            // DRAW BORDERS

            list<Landmass::border_coords> border_pieces = it->get_vertical_border_pieces();
            for(list<Landmass::border_coords>::iterator jt = border_pieces.begin(); jt != border_pieces.end(); jt++)
            {
                label = new QLabel(this);
                label->setGeometry(jt->x, jt->y, 3, 10);
                label->setStyleSheet(("QLabel { background-color : " + border_colors[i-1] + "}").c_str());
            }
            border_pieces = it->get_horizontal_border_pieces();
            for(list<Landmass::border_coords>::iterator jt = border_pieces.begin(); jt != border_pieces.end(); jt++)
            {
                label = new QLabel(this);
                label->setGeometry(jt->x, jt->y, 10, 3);
                label->setStyleSheet(("QLabel { background-color : " + border_colors[i-1] + "}").c_str());
            }
            i++;

        }
        if(landmasses->size()%3!=0)
            y+=60;
        label = new QLabel(this);
        label->setGeometry(10,y,500,20);
        string map_key = string("<html><b>Map key: </b>") +
                "<img src=\"" + img_path + "water" + img_format + "\"> = Water, </html>" +
                "<img src=\"" + img_path + "land" + img_format + "\"> = Land, </html>" +
                "<img src=\"" + img_path + "tree" + img_format + "\"> = Tree, </html>" +
                "<img src=\"" + img_path + "mountain" + img_format + "\"> = Mountain, </html>" +
                "<img src=\"" + img_path + "building" + img_format + "\"> = Building</html>";
        label->setText(map_key.c_str());
        QPushButton* another_map = new QPushButton(this);
        another_map->setGeometry((map_max_width_index+1)*10-120,y,120,25);
        another_map->setText("Evaluate another map");
        this->connect(another_map, SIGNAL(clicked()), this, SLOT(on_another_map_clicked()));
        this->resize((map_max_width_index+1)*10+20, y+40);
        this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
        this->show();
    }
    else
    {
        QMessageBox::critical(this, tr(app_name),
                                   tr(("Couldn't open map:\n" + map_name).c_str()),
                                   QMessageBox::Ok);
        dialog->show();
    }
}


void LandmassDetector::on_another_map_clicked()
{
    this->hide();
    this->deleteLater();
    dialog->show();
}
