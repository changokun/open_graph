<?php

class open_graph_image {

	const NS = 'image:';

	// public $data = array('og:image:url' => null, 'og:image:secure_url' => null, 'og:image:type' => null, 'og:image:width' => null, 'og:image:height' => null);
	public $url;
	public $secure_url;
	public $type;
	public $width;
	public $height;

	public function __construct($url = null) {
		if( ! empty($url)) $this->url = $url;
	}

	public function __toString() {
		$data = $this->get_data_structure();
		return open_graph::get_tags($data);
	}

	public function get_data_structure() {
		// if no url, then no data.
		if(empty($this->url)) return array();
		if(empty($this->secure_url) and empty($this->type) and empty($this->width) and empty($this->height)) {
			// simplify - remove the colon and jsut supply the url
			return array(str_replace(':', '', static::NS) . ' ' . $this->url);
		}
		$data = array();
		foreach(array_keys(get_class_vars(get_called_class())) as $property_name) {
			// echo "[$property_name]";
			if( ! empty($this->$property_name)) $data[] = static::NS . $property_name . ' ' . $this->$property_name;
		}
		return $data;
	}

}


/*
The og:image property has some optional structured properties:

og:image:url - Identical to og:image.
og:image:secure_url - An alternate url to use if the webpage requires HTTPS.
og:image:type - A MIME type for this image.
og:image:width - The number of pixels wide.
og:image:height - The number of pixels high.
A full image example:

<meta property="og:image" content="http://example.com/ogp.jpg" />
<meta property="og:image:secure_url" content="https://secure.example.com/ogp.jpg" />
<meta property="og:image:type" content="image/jpeg" />
<meta property="og:image:width" content="400" />
<meta property="og:image:height" content="300" />

*/