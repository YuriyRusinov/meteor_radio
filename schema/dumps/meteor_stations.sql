--
-- PostgreSQL database dump
--

-- Dumped from database version 9.6.10
-- Dumped by pg_dump version 9.6.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: tbl_meteor_station; Type: TABLE; Schema: public; Owner: yrusinov
--

CREATE TABLE public.tbl_meteor_station (
    id bigint DEFAULT nextval('public.tbl_meteor_station_id_seq'::regclass) NOT NULL,
    station_number bigint NOT NULL,
    station_address character varying,
    longitude double precision,
    latitude double precision,
    srid bigint DEFAULT 4326 NOT NULL,
    frequency double precision,
    station_type bigint DEFAULT 1 NOT NULL,
    id_message_gen bigint
)
WITH (MACS=FALSE);


ALTER TABLE public.tbl_meteor_station OWNER TO yrusinov;

--
-- Name: TABLE tbl_meteor_station; Type: MAC LABEL; Schema: public; Owner: yrusinov
--

MAC LABEL ON TABLE public.tbl_meteor_station IS '{0,0}';


--
-- Name: TABLE tbl_meteor_station; Type: MAC CCR; Schema: public; Owner: yrusinov
--

MAC CCR ON TABLE public.tbl_meteor_station IS ON;


--
-- Data for Name: tbl_meteor_station; Type: TABLE DATA; Schema: public; Owner: yrusinov
--

INSERT INTO public.tbl_meteor_station (id, station_number, station_address, longitude, latitude, srid, frequency, station_type, id_message_gen) VALUES (1, 2, '192.168.117.187', 32.5, 67.5, 4326, 4.5, 1, 6);
INSERT INTO public.tbl_meteor_station (id, station_number, station_address, longitude, latitude, srid, frequency, station_type, id_message_gen) VALUES (3, 4, '192.168.117.178', 45, 67.5, 4326, 4.5, 1, 7);
INSERT INTO public.tbl_meteor_station (id, station_number, station_address, longitude, latitude, srid, frequency, station_type, id_message_gen) VALUES (2, 3, '192.168.117.169', 50.5, 75, 4326, 4.5, 1, 10);


--
-- Name: tbl_meteor_station pk_tbl_meteor_station; Type: CONSTRAINT; Schema: public; Owner: yrusinov
--

ALTER TABLE ONLY public.tbl_meteor_station
    ADD CONSTRAINT pk_tbl_meteor_station PRIMARY KEY (id);


--
-- Name: tbl_meteor_station FK_tbl_meteor_station_REF_id_message_gen; Type: FK CONSTRAINT; Schema: public; Owner: yrusinov
--

ALTER TABLE ONLY public.tbl_meteor_station
    ADD CONSTRAINT "FK_tbl_meteor_station_REF_id_message_gen" FOREIGN KEY (id_message_gen) REFERENCES public.tbl_random_gen(id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: tbl_meteor_station FK_tbl_meteor_station_REF_srid; Type: FK CONSTRAINT; Schema: public; Owner: yrusinov
--

ALTER TABLE ONLY public.tbl_meteor_station
    ADD CONSTRAINT "FK_tbl_meteor_station_REF_srid" FOREIGN KEY (srid) REFERENCES public.spatial_ref_sys(srid) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- Name: tbl_meteor_station FK_tbl_meteor_station_REF_station_type; Type: FK CONSTRAINT; Schema: public; Owner: yrusinov
--

ALTER TABLE ONLY public.tbl_meteor_station
    ADD CONSTRAINT "FK_tbl_meteor_station_REF_station_type" FOREIGN KEY (station_type) REFERENCES public.tbl_meteor_station_type(id) ON UPDATE CASCADE ON DELETE RESTRICT;


--
-- PostgreSQL database dump complete
--

