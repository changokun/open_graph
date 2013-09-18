<?php

class open_graph_profile {

	//profile - Namespace URI: http://ogp.me/ns/profile#
	const NS = 'profile:';

	public $first_name; // string - A name normally given to an individual by a parent or self-chosen.
	public $last_name; // string - A name inherited from a family or marriage and by which the individual is commonly known.
	public $username; // string - A short unique string to identify them.
	public $gender; // enum(male, female) - Their gender.

	public function __toString() {
		$data = $this->get_data_structure();
		return open_graph::get_tags($data);
	}

	public function get_data_structure() {
		$data = array();
		foreach(array_keys(get_class_vars(get_called_class())) as $property_name) {
			if( ! empty($this->$property_name)) $data[] = static::NS . $property_name . ' ' . $this->$property_name;
		}
		return $data;
	}

}