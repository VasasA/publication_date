<?php

/**
 * @file
 * Provide views data and handlers for the Publication Date module.
 */

/**
 * Implements hook_views_data().
 */
function publication_date_views_data() {
  $data = array();

  $data['publication_date']['table']['group'] = t('Content');

  // Declare an implicit relationship to the node table.
  $data['publication_date']['table']['join']['node'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
  );

  // Description of the published_at field.
  $data['publication_date']['published_at'] = array(
    'title' => t('Published at'),
    'help' => t('Date when the content was first published.'),
    'field' => array(
      'handler' => 'views_handler_field_publication_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_publication_date',
      'label' => t('Published at'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_publication_date',
    ),
  );

  $data['publication_date']['published_at_fulldate'] = array(
    'title' => t('Published at date'),
    'help' => t('Published date in the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'published_at',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['publication_date']['published_at_year_month'] = array(
    'title' => t('Published at year + month'),
    'help' => t('Published date in the form of YYYYMM.'),
    'argument' => array(
      'field' => 'published_at',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['publication_date']['published_at_year'] = array(
    'title' => t('Published at year'),
    'help' => t('Published date in the form of YYYY.'),
    'argument' => array(
      'field' => 'published_at',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['publication_date']['published_at_month'] = array(
    'title' => t('Published at month'),
    'help' => t('Published date in the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'published_at',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['publication_date']['published_at_day'] = array(
    'title' => t('Published at day'),
    'help' => t('Published date in the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'published_at',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['publication_date']['published_at_week'] = array(
    'title' => t('Published at week'),
    'help' => t('Published date in the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'published_at',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  return $data;
}
