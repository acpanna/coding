-- phpMyAdmin SQL Dump
-- version 2.11.1.2
-- http://www.phpmyadmin.net
--
-- Host: dbnfs
-- Erstellungszeit: 30. September 2013 um 01:59
-- Server Version: 5.0.22
-- PHP-Version: 5.3.10-1ubuntu3.7

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Datenbank: `skm_localisation`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `entries`
--

CREATE TABLE IF NOT EXISTS `entries` (
  `id` int(11) NOT NULL auto_increment,
  `var_id` int(11) NOT NULL default '0',
  `language_id` int(11) NOT NULL default '0',
  `text` text NOT NULL,
  `author_id` int(11) NOT NULL,
  `date` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `var_id` (`var_id`,`language_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1284 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `languages`
--

CREATE TABLE IF NOT EXISTS `languages` (
  `id` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `shortkey` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL auto_increment,
  `lastname` text NOT NULL,
  `firstname` text NOT NULL,
  `uname` text NOT NULL,
  `password` text NOT NULL,
  `edit` text NOT NULL,
  `ref` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=16 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `vars`
--

CREATE TABLE IF NOT EXISTS `vars` (
  `id` int(11) NOT NULL auto_increment,
  `var` text NOT NULL,
  `image` text,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=223 ;
