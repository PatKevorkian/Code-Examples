-- phpMyAdmin SQL Dump
-- version 4.0.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 26, 2015 at 01:50 PM
-- Server version: 5.1.73
-- PHP Version: 5.3.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `pageVisits`
--

-- --------------------------------------------------------

--
-- Table structure for table `visitInfo`
--

CREATE TABLE IF NOT EXISTS `visitInfo` (
  `page_name` varchar(250) NOT NULL,
  `visit_date` date NOT NULL,
  `visit_time` time NOT NULL,
  `previous_page` varchar(250) NOT NULL,
  `request_method` varchar(10) NOT NULL,
  `remote_host` varchar(250) NOT NULL,
  `remote_port` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `visitInfo`
--

INSERT INTO `visitInfo` (`page_name`, `visit_date`, `visit_time`, `previous_page`, `request_method`, `remote_host`, `remote_port`) VALUES
('regexp.php', '2015-03-02', '10:50:09', 'regexp.html', 'post', 'www.cs.csi.cuny.edu', 80),
('regexp.php', '2015-02-17', '01:38:56', 'regexp.html', 'post', 'www.cs.csi.cuny.edu', 80),
('www.google.com', '2015-03-10', '11:37:56', 'regexp.html', 'post', 'www.google.com', 80),
('xch.csi.cuny.edu', '2015-01-22', '11:37:56', 'search.php', 'post', 'www.google.com', 80),
('second.php', '2015-01-24', '09:00:07', 'first.php', 'post', 'csdabase.cs.edu', 80),
('fourth.php', '2015-01-24', '09:10:10', 'third.php', 'post', 'csdabase.cs.edu', 80),
('fourth.php', '2015-01-24', '09:22:10', 'third.php', 'post', 'csdabase.cs.edu', 80),
('fourth.php', '2015-01-24', '09:25:10', 'third.php', 'post', 'csdabase.cs.edu', 80),
('www.google.com', '2015-03-08', '01:03:54', 'www.yahoo.com', 'get', 'www.google.com', 8080),
('netmail.verizon.net', '2015-03-17', '12:09:08', 'www.yahoo.com', 'get', 'www.verizon.net', 80);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
