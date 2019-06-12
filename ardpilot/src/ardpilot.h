//
//  ardpilot.h
//  
//
//  Created by Olivier Messiant on 28/11/2016.
//
//

#ifndef ardpilot_h
#define ardpilot_h

struct cellule
{
    unsigned char piece; // 4 msb : pièce, 4 lsb : zone dans la pièce
    // correspond aux deux premiers codes du fichier CSV, chacun entre 0 et F
    // par convention 00 = vide, 0F = mur
    unsigned char WifiMatrix; // 0 : pas de matrice de référence ; n = numéro de la matrice mesurée
};

#define APPT_L 193
#define APPT_W  93
#define BORDER 10

struct _ssid
{
    int updated;    // used during learning process
    int val;        // SSID strength
    char label[32]; // SSID name
};

struct wifiref
{
    unsigned int zone;
    char name[32];
    struct _ssid ssid[4][10]; // la matrice elle-même
    int i; // ordonnée dans le plan de l'appart (unused)
    int j; // abscisse dans le plan de l'appart (unused)
    int Releves; // nombre de mesures
};

// prototypes

void control_message (unsigned char action, char *message);
int exec_cmd (char *buffer, int debug_mode);
int write_ard (int fd, char *message);
void interpret_ard (char *buffer, int debug_mode);
void exit_on_failure (char *reason);
void init_command_mode ();
void ard_block_mode ();
void ard_async_mode ();

// from environment.c
void check_free_mem (unsigned char sequence);
void check_compas (unsigned char sequence);
void check_voltage ();
void get_top_wifi (char sequence);
void check_wifi_environment (char sequence);
int get_health ();
int analyze_environment ();
int record_wifi_reference (int n);

// from drawing.c
void draw_plan ();
void consolidate_points (char *buffer, char segment, char orientation, double X[], double Y[], double mesures[]);
void draw_segment (char *buffer, char segment, char orientation);
void draw_line (int xs, int ys, int xe, int ye);


// from read_config
void read_plan();
void read_matrices();
void read_wifi_matrixes();
void write_wifi_matrixes();
FILE *open_wifi_matrix_file (int MatRef);
void close_wifi_matrix_file (FILE *fd);

// from commandes.c
int oriente_robot (int cap_souhaite, int tolerance);
int bloc_get_top_wifi ();
int locate_myself ();
int stop_command_script(char *ScriptName);
int run_command_script(char *ScriptName);

#endif /* ardpilot_h */
