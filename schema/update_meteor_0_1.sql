insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(513, 40, 5, 'random_state', 'Состояние датчика случайных чисел', 'Состояние датчика случайных чисел', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(514, 40, 5, 'message_content', 'Содержание сообщения', 'Содержание сообщения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(515, 1, 5, 'message_was_sent', 'Флаг отправки сообщения', 'Флаг отправки сообщения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(516, 2, 5, 'id_meteor_station_from', 'Метеорная радиостанция', 'Метеорная радиостанция', 'tbl_meteor_station', 'id', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(517, 2, 5, 'id_meteor_station_to', 'Метеорная радиостанция', 'Метеорная радиостанция', 'tbl_meteor_station', 'id', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(518, 8, 5, 'rand_seed', 'Стартовая величина датчика случайных чисел', 'Стартовая величина датчика случайных чисел',  null::varchar, null::varchar, false) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (722, 509, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (723, 509, 513, null, false, false, 2) on conflict do nothing; -- state
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (724, 509, 518, null, false, false, 3) on conflict do nothing; -- seed

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(509, 10, null::integer, false, 'Таблица датчиков случайных чисел для метеорных радиостанций', 'METEOR_509', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(510, 8, 509, true, 'Справочник датчиков случайных чисел для метеорных радиостанций', 'METEOR_510', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(511, 10, null::integer, false, 'Таблица сообщений', 'METEOR_511', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(512, 8, 511, true, 'Справочник сообщений', 'METEOR_512', null::varchar, true) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (722, 509, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (723, 509, 513, null, false, false, 2) on conflict do nothing; -- state
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (724, 509, 518, null, false, false, 3) on conflict do nothing; -- seed

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (725, 511, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (726, 511, 514, null, false, false, 2) on conflict do nothing; -- message content
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (727, 511, 515, 'false', true, false, 3) on conflict do nothing; -- message was sent
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (728, 511, 516, null, true, true, 4) on conflict do nothing; -- from station
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (729, 511, 517, null, true, true, 5) on conflict do nothing; -- to station

insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (124, 1, 510, 'Справочник датчиков случайных чисел', null::varchar, 'tbl_random_states', 'Датчики случайных чисел', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (125, 1, 512, 'Справочник сообщений', null::varchar, 'tbl_meteor_messages', 'Сообщения', false, current_timestamp, true) on conflict do nothing;

