#pragma once
#include "project_config.h"
#include "usart2.h"
#include "pin_setup.h"
#include "tools.h"
#include "time_service.h"
#include "math.h"

enum camera_pos
{
  front_camera,
  omni_camera
};

class camera
{
	public:
		camera(bool Camera_pos, pin &tx, pin &rx);
		void getData();
    //uint16_t lead_to_degree_borders(int num);
    void calculate_pos(int16_t angle, bool side);
		int16_t get_x();
		int16_t get_y();
    int16_t get_forward_angle();
    int16_t get_backward_angle();
    int16_t get_forward_distance();
    int16_t get_backward_distance();
    uint8_t get_data_state();
    int16_t get_ball_angle();
    int16_t get_abs_ball_angle();
    int16_t get_ball_distance();
    int16_t get_ball_loc_x();
    int16_t get_ball_loc_y();
    int16_t get_ball_abs_x();
    int16_t get_ball_abs_y();
    int16_t get_old_b_x();
    int get_old_b_y();
    int get_dS();
    int get_dSSoft();
    int16_t get_dbx();
    int get_dby();
    bool is_first_data_received();
    bool check_ball_seen(uint32_t _dT = 1000);
    uint32_t get_ball_seen_time();

	private:
    bool _camera_pos;
    polar_vector get_angle_to_point(int16_t _robot_x, int16_t _robot_y, int16_t _point_x, int16_t _point_y);
		int8_t sign;
		pin m_rx, m_tx;
		uint8_t camera_data;
		int16_t _data;
		volatile int _yellow_distance;
    int _yellow_angle;
    int _blue_distance;
		volatile int _blue_angle;
    int _ball_angle;
    int _ball_loc_angle;
    int _abs_ball_angle;
    int _ball_distance;
    int _ball_loc_x, _ball_loc_y;
    int _ball_abs_x, _ball_abs_y;
    int _front_angle;
    int _front_distance;
    int _backward_distance;
    int _backward_angle;
    int _center_distance;
    int _center_angle;
    int _x, _y;
    int _old_x, _old_y;
    volatile int _dbx, _dby;
    int _x_centered, _y_centered;
    int _center_y;
    double _forward_sin, _backward_sin;
    double _forward_x, _backward_x;
    int _dist1, _dist2;
		int16_t old_data;
		int8_t near_gate_color;
		bool color; //1=y 0=b
		bool num;
		bool finaly;
		bool read;
    bool _received;
    bool _first_receive;
    bool _yellow_first_receive, _blue_first_receive;
    bool _ball_is_seen;
		uint8_t data[8];
		uint8_t crc8(uint8_t* data, int len);
    uint8_t _state;
    uint32_t _ball_d_timer, _ball_timer;
    float _ball_k;
    int ball_new_abs_x, ball_new_abs_y;
    int ball_new_loc_x, ball_new_loc_y, ball_new_loc_angle, ball_new_abs_angle, ball_new_distance;
    float _ball_x_soft, _ball_y_soft;
    int _dS, _dSSoft;
    float _robot_k, k_dSSoft;
    float _robot_x_soft, _robot_y_soft;
    double _gates_average_k;    
    uint8_t _length_between_gates;
    uint32_t get_ball_new_value_timer;
};
