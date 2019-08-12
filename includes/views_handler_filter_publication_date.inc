<?php

/**
 * @file
 * Definition of views_handler_filter_publication_date.
 */

/**
 * Filter to handle publication dates stored as a timestamp.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_publication_date extends views_handler_filter_date {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['null_date'] = array('default' => 'null');

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['null_date'] = array(
      '#type' => 'radios',
      '#title' => t('Treat empty publication date as'),
      '#options' => array(
        'null' => t('NULL'),
        'now' => t('Current time'),
        'created' => t('Content created date'),
        'changed' => t('Content last modified date'),
      ),
      '#description' => t('How should we treat content without a publication date?'),
      '#default_value' => $this->options['null_date'],
    );
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();

    if ($this->options['null_date'] == 'null') {
      $field = "$this->table_alias.$this->real_field";
    }
    else {
      $field_name = $this->real_field . '_or_' . $this->options['null_date'];

      switch ($this->options['null_date']) {
        case 'now':
          $alt_value = REQUEST_TIME;
          break;

        case 'created':
          $alt_value = "node.created";
          break;

        case 'changed':
          $alt_value = "node.changed";
          break;
      }

      $field = "COALESCE($this->table_alias.$this->real_field, $alt_value)";
    }

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field);
    }
  }

}
