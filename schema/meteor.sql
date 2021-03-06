insert into tbl_parameters_groups (id, name) values( 5, 'Атрибуты метеорного радио') on conflict do nothing;

insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(501, 8, 5, 'station_number', 'Номер станции', 'Номер станции', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(502, 7, 5, 'frequency', 'Частота вещания', 'Частота вещания', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(503, 2, 5, 'id_message_gen', 'Генератор случайных сообщений', 'Генератор случайных сообщений', 'tbl_random_gen', 'description', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(504, 2, 5, 'station_type', 'Тип станции', 'Тип станции', 'tbl_meteor_station_type', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(505, 2, 5, 'id_distribution_func', 'Функция распределения', 'Функция распределения', 'tbl_rand_distrib', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(506, 7, 5, 'val_min', 'Минимальная величина при равномерном распределении', 'Минимальная величина при равномерном распределении', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(507, 7, 5, 'val_max', 'Максимальная величина при равномерном распределении', 'Максимальная величина при равномерном распределении', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(508, 7, 5, 'mathematical_expectation_exp', 'Математическое ожидание при экспоненциальном распределении', 'Математическое ожидание при экспоненциальном распределении', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(509, 7, 5, 'mathematical_expectation', 'Математическое ожидание при нормальном распределении', 'Математическое ожидание при нормальном распределении', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(510, 7, 5, 'standard', 'Стандарт при нормальном распределении', 'Стандарт при нормальном распределении', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(511, 9, 5, 'station_address', 'ip-адрес станции', 'ip-адрес станции', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(512, 7, 5, 'scale', 'Параметр масштаба при распределении Рэлея', 'Параметр масштаба при распределении Рэлея', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(513, 40, 5, 'random_state', 'Состояние датчика случайных чисел', 'Состояние датчика случайных чисел', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(514, 40, 5, 'message_content', 'Содержание сообщения', 'Содержание сообщения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(515, 1, 5, 'message_was_sent', 'Флаг отправки сообщения', 'Флаг отправки сообщения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(516, 2, 5, 'id_meteor_station_from', 'Метеорная радиостанция', 'Метеорная радиостанция', 'tbl_meteor_station', 'id', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(517, 2, 5, 'id_meteor_station_to', 'Метеорная радиостанция', 'Метеорная радиостанция', 'tbl_meteor_station', 'id', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values(518, 8, 5, 'rand_seed', 'Стартовая величина датчика случайных чисел', 'Стартовая величина датчика случайных чисел',  null::varchar, null::varchar, false) on conflict do nothing;
select setval('tbl_parameters_id_seq', 1000, true);

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(501, 10, null::integer, false, 'Таблицы типов метеорных радиостанций', 'METEOR_501', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(502, 8, 501, true, 'Справочник типов метеорных радиостанций', 'METEOR_502', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(503, 10, null::integer, false, 'Таблицы метеорных радиостанций', 'METEOR_503', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(504, 8, 503, true, 'Справочник метеорных радиостанций', 'METEOR_504', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(505, 10, null::integer, false, 'Таблицы датчиков случайных чисел для метеорных радиостанций', 'METEOR_505', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(506, 8, 505, true, 'Справочник датчиков случайных чисел для метеорных радиостанций', 'METEOR_506', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(507, 10, null::integer, false, 'Таблицы функций распределения случайных чисел для метеорных радиостанций', 'METEOR_507', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(508, 8, 507, true, 'Справочник функций распределения случайных чисел для метеорных радиостанций', 'METEOR_508', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(509, 10, null::integer, false, 'Таблица датчиков случайных чисел для метеорных радиостанций', 'METEOR_509', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(510, 8, 509, true, 'Справочник датчиков случайных чисел для метеорных радиостанций', 'METEOR_510', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(511, 10, null::integer, false, 'Таблица сообщений', 'METEOR_511', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(512, 8, 511, true, 'Справочник сообщений', 'METEOR_512', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(513, 10, null::integer, false, 'Таблица маршрутов', 'METEOR_513', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values(514, 8, 513, true, 'Справочник маршрутов', 'METEOR_514', null::varchar, true) on conflict do nothing;

select setval('tbl_communication_categories_id_seq', 600, true);

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (700, 501, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (701, 501, 2, null, true, true, 2) on conflict do nothing; -- name

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (702, 503, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (703, 503, 501, null, true, false, 2) on conflict do nothing; -- station_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (704, 503, 511, null, false, false, 3) on conflict do nothing; -- ip address
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (705, 503, 89, null, false, false, 4) on conflict do nothing; -- longitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (706, 503, 88, null, false, false, 5) on conflict do nothing; -- latitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (707, 503, 100, '4326'::varchar, true, false, 6) on conflict do nothing; -- srid
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (708, 503, 502, null, false, false, 7) on conflict do nothing; -- frequency
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (709, 503, 504, '1'::varchar, true, false, 8) on conflict do nothing; -- station_type
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (710, 503, 503, null, false, false, 9)  on conflict do nothing; -- messages generator

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (711, 505, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (712, 505, 3, null, false, false, 2) on conflict do nothing; -- description
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (713, 505, 505, null, true, false, 3) on conflict do nothing; -- id_distribution_func
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (714, 505, 506, null, false, false, 4) on conflict do nothing; -- val_min
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (715, 505, 507, null, false, false, 5) on conflict do nothing; -- val_max
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (716, 505, 508, null, false, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (717, 505, 509, null, false, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (718, 505, 510, null, false, false, 8) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (719, 505, 512, null, false, false, 9) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (720, 507, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (721, 507, 2, null, true, true, 2) on conflict do nothing; -- name

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (722, 509, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (723, 509, 513, null, false, false, 2) on conflict do nothing; -- state
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (724, 509, 518, null, false, false, 3) on conflict do nothing; -- seed

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (725, 511, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (726, 511, 514, null, false, false, 2) on conflict do nothing; -- message content
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (727, 511, 515, 'false', true, false, 3) on conflict do nothing; -- message was sent
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (728, 511, 516, null, true, true, 4) on conflict do nothing; -- from station
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (729, 511, 517, null, true, true, 5) on conflict do nothing; -- to station

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (730, 513, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (731, 513, 516, null, true, false, 2) on conflict do nothing; -- from station
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (732, 513, 517, null, true, false, 3) on conflict do nothing; -- to station
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (733, 513, 3, null, false, false, 4) on conflict do nothing; -- description

select setval('tbl_cat_params_id_seq', 1000, true);

--
-- Справочники
--
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (120, 1, 502, 'Справочник типов метеорных радиостанций', null::varchar, 'tbl_meteor_station_type', 'Типы метеорных радиостанций: оконечная или промежуточная', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (121, 1, 508, 'Справочник функций распределения случайных сообщений', null::varchar, 'tbl_rand_distrib', 'Функции распределения случайных чисел', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (122, 1, 506, 'Справочник генераторов случайных сообщений', null::varchar, 'tbl_random_gen', 'Генератор случайных чисел', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (123, 1, 504, 'Справочник метеорных радиостанций', null::varchar, 'tbl_meteor_station', 'Метеорная радиостанция', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (124, 1, 510, 'Справочник датчиков случайных чисел', null::varchar, 'tbl_random_states', 'Датчики случайных чисел', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (125, 1, 512, 'Справочник сообщений', null::varchar, 'tbl_meteor_messages', 'Сообщения', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (126, 1, 514, 'Справочник маршрутов', null::varchar, 'tbl_station_route_metrics', 'Маршруты доставки сообщений', false, current_timestamp, true) on conflict do nothing;
select setval('tbl_communication_objects_references_id_seq', 300, true);

insert into tbl_meteor_station_type(id, name) values (1, 'Оконечная') on conflict do nothing;
insert into tbl_meteor_station_type(id, name) values (2, 'Промежуточная') on conflict do nothing;
select setval('tbl_meteor_station_type_id_seq', 2, true);

insert into tbl_rand_distrib(id, name) values (1, 'Равномерное распределение') on conflict do nothing;
insert into tbl_rand_distrib(id, name) values (2, 'Экспоненциальное распределение') on conflict do nothing;
insert into tbl_rand_distrib(id, name) values (3, 'Нормальное распределение') on conflict do nothing;
insert into tbl_rand_distrib(id, name) values (4, 'Распределение Рэлея') on conflict do nothing;
select setval('tbl_rand_distrib_id_seq', 4, true);

