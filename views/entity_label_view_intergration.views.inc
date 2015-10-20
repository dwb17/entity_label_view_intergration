<?php
/**
 * @file
 * Provide views data for modules making use of the entity CRUD API.
 */

/**
 * Implements hook_views_data().
 * Expose entity label to views API
 */
function entity_label_view_intergration_views_data() {
  $data = array();

  // Expose generally usable entity-related fields.
  foreach (entity_get_info() as $entity_type => $info) {
    // Add Entity Label property
    if (!empty($info['entity keys']['label']) || !empty($info['label callback'])) {
      // Check if entity_uri is supported for this entity type.
      $has_uri = !empty($info['uri callback']);
      if (!$has_uri && is_array($info['bundles'])) {
        $bundle_info = current($info['bundles']);
        $has_uri = !empty($bundle_info['uri_callback']);
      }
      $data['views_entity_' . $entity_type]['label'] = array(
        'title' => t('Entity label'),
        'help' => t('The label of the @entity-type entity.', array('@entity-type' => $info['label'])),
        'field' => array(
          'handler' => 'entity_label_view_intergration_views_handler_field_label',
          'type' => $entity_type,
          'has uri' => $has_uri,
        ),
      );
    }    
  }  
  return $data;
}