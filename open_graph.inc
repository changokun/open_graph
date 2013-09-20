<?php

abstract class open_graph {

	const ROOT_NS = 'og:';
	public $title;
	public $description;
	public $type; // can only be set by instantiating an extending class.
	public $image; // an array of open graph image objects
	public $url; // canonical url.

	protected static $root_properties = array('title', 'type', 'image', 'url', 'description');

	public function __toString() {
		// todo validate the basics, at least.

		$data = $this->get_data_structure();
		return PHP_EOL . '<!-- ' . __CLASS__ . ' -->' . self::get_tags($data);
	}

	public function json() {
		return json_encode($this->get_data_structure());
	}

	private function get_data_structure() {
		$data = array();

		foreach($this as $property => $value) {
			// echo '<br>' . $property;
            if(is_null($value)) {
                // do nothing.
            } elseif(is_scalar($value)) {
				if(in_array($property, self::$root_properties)) {
					$data[] = self::ROOT_NS . $property . ' ' . $value;
				} else {
					$data[] = static::NS . $property . ' ' . $value;
				}
			} elseif(is_array($value)) {
				foreach($value as $presumed_object) {
					foreach($presumed_object->get_data_structure() as $datum) {
						if(in_array($property, self::$root_properties)) {
							$data[] = self::ROOT_NS . $datum;
						} else {
							$data[] = static::NS . $datum;
						}
					}
				}
			} elseif(is_object($value) and strpos(get_class($value), 'open_graph') === 0) {
				foreach($value->get_data_structure() as $datum) $data[] = static::NS . $property . ':' . $datum;
			} else {
				m::death($value);
				die('<hr>' . @$something . '<br>Died on line ' . __LINE__ . ' of ' . __FILE__);///////////////////////////////////////////////////////////////////////////////////////////////////
				trigger_error('bad property in an opengraph object.', E_USER_NOTICE);
			}
		}
		// m::dump($data, 'weee');

		return $data;
	}

	/**
	* @returns true on success, false on error.
	*
	* @param string $url full absolute canonical url
	*/
	public function set_url($url = null) {
		// must be full absolute canonical url with no funny business.
		$url_info = parse_url($url);
		if( ! empty($url_info['query']) or ! empty($url_info['fragment'])) {
			trigger_error('eh.... for now let us not allow query vars  nor hash-fragments on canonical urls, okay? your og tag has failed.', E_USER_WARNING);
			return false;
		}
		if(
			empty($url_info['scheme'])
			or empty($url_info['host'])
			or ! empty($url_info['port'])
			or ! empty($url_info['user'])
			or ! empty($url_info['pass'])
		) return false;
		$this->url = $url;
	}

	public function set_image(open_graph_image $open_graph_image) {
		$this->image[] = $open_graph_image;
	}

	public function set_images($open_graph_images) {
		if( ! is_array($open_graph_images)) return false;
		foreach($open_graph_images as $open_graph_image) $this->set_image($open_graph_image);
	}

	public function set_description($descritption = null) {
		$descritption = trim(html_entity_decode($descritption, null, 'utf-8'));
		if(empty($descritption)) return false;
		if(strlen($descritption) > 256) $descritption = substr($descritption, 0, 254) . ' &hellip;'; // todo replace with utf-8
		$this->description = $descritption;
	}

	/**
	* make the actual tags
	*
	* @param mixed $data
	* @param boolean $readable // if true will insert line breaks to make the output more readable
	* @param boolean $verbose // if true will insert any 'notes' as html comments
	*/
	protected static function get_tags($data, $readable = true) {
		$output = $readable ? PHP_EOL : '';
		foreach($data as $datum) {
			$pos = strpos($datum, ' ');
			$key = substr($datum, 0, $pos);
			$value = substr($datum, $pos + 1);
			$output .= '<meta property="'. $key . '" content="' . $value . '" />';
			$output .= $readable ? PHP_EOL : '';
		}
		return $output;
	}

    public function get_array_of_tags() {
        $data = $this->get_data_structure();
        $str = '<!-- open_graph -->' . PHP_EOL . static::get_tags($data);
        return array_filter(explode(PHP_EOL, $str));
    }

}
